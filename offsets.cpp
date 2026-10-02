#include "mc_offsets.hpp"

#include <cstring>

namespace mc {

bool isSupportedBuild(const std::uint8_t* base) {
    std::int32_t peOffset;
    std::uint32_t stamp;
    std::memcpy(&peOffset, base + 0x3C, sizeof peOffset);
    std::memcpy(&stamp, base + peOffset + 8, sizeof stamp);
    return stamp == kPeTimestamp;
}

LocalPlayer* getLocalPlayer(ClientInstance* client) {
    using Fn = LocalPlayer* (*)(ClientInstance*);
    return (*reinterpret_cast<Fn**>(client))[slot::ClientInstanceGetLocalPlayer](client);
}

EntityContext* entityContext(Actor* actor) {
    return reinterpret_cast<EntityContext*>(reinterpret_cast<char*>(actor) + offset::ActorEntityContext);
}

StateVectorComponent* stateVector(Actor* actor) {
    StateVectorComponent* component;
    std::memcpy(&component, reinterpret_cast<char*>(actor) + offset::ActorStateVectorPtr, sizeof component);
    return component;
}

AABBShapeComponent* aabbShape(Actor* actor) {
    AABBShapeComponent* component;
    std::memcpy(&component, reinterpret_cast<char*>(actor) + offset::ActorAABBShapePtr, sizeof component);
    return component;
}

ActorRotationComponent* rotation(Actor* actor) {
    ActorRotationComponent* component;
    std::memcpy(&component, reinterpret_cast<char*>(actor) + offset::ActorRotationPtr, sizeof component);
    return component;
}

ActorWalkAnimationComponent* walkAnimation(Actor* actor) {
    ActorWalkAnimationComponent* component;
    std::memcpy(&component, reinterpret_cast<char*>(actor) + offset::ActorWalkAnimationPtr, sizeof component);
    return component;
}

void* componentStorage(void* enttRegistry, std::uint32_t hash) {
    using namespace entt_layout;
    using detail::readU32;
    using detail::readU64;
    const std::uint64_t registry = reinterpret_cast<std::uintptr_t>(enttRegistry);
    const std::uint64_t buckets = readU64(registry + RegistryBuckets), bucketsEnd = readU64(registry + RegistryBuckets + 8);
    const std::uint64_t nodes = readU64(registry + RegistryNodes), nodesEnd = readU64(registry + RegistryNodes + 8);
    if (bucketsEnd <= buckets) {
        return nullptr;
    }
    std::uint64_t index = readU64(buckets + (hash & ((bucketsEnd - buckets) / 8 - 1)) * 8);
    while (index != ~0ull) {
        const std::uint64_t node = nodes + index * PoolNodeSize;
        if (node >= nodesEnd) {
            return nullptr;
        }
        if (readU32(node + PoolNodeHash) == hash) {
            return reinterpret_cast<void*>(static_cast<std::uintptr_t>(readU64(node + PoolNodeStorage)));
        }
        index = readU64(node);
    }
    return nullptr;
}

std::int64_t denseIndex(void* storage, std::uint32_t entity) {
    using namespace entt_layout;
    using detail::readU32;
    using detail::readU64;
    const std::uint64_t pool = reinterpret_cast<std::uintptr_t>(storage);
    const std::uint32_t slot = entity & EntityMask;
    const std::uint64_t sparse = readU64(pool + StorageSparse), sparseEnd = readU64(pool + StorageSparse + 8);
    if (slot / SparsePage >= (sparseEnd - sparse) / 8) {
        return -1;
    }
    const std::uint64_t sparsePage = readU64(sparse + (slot / SparsePage) * 8);
    if (sparsePage == 0) {
        return -1;
    }
    const std::uint32_t element = readU32(sparsePage + (slot % SparsePage) * 4);
    if ((element ^ (entity & ~EntityMask)) > EntityMask - 1) {
        return -1;
    }
    return element & EntityMask;
}

bool hasComponent(void* storage, std::uint32_t entity) {
    return storage != nullptr && denseIndex(storage, entity) >= 0;
}

void* componentOf(void* storage, std::uint32_t entity, std::size_t size) {
    using namespace entt_layout;
    const std::int64_t dense = denseIndex(storage, entity);
    if (dense < 0) {
        return nullptr;
    }
    const std::uint64_t pages = detail::readU64(reinterpret_cast<std::uintptr_t>(storage) + StoragePayload);
    const std::uint64_t page = pages ? detail::readU64(pages + (static_cast<std::uint64_t>(dense) / PayloadPage) * 8) : 0;
    if (page == 0) {
        return nullptr;
    }
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(page + (static_cast<std::uint64_t>(dense) % PayloadPage) * size));
}

void* tryGetComponentRaw(void* enttRegistry, std::uint32_t entity, std::uint32_t hash, std::size_t size) {
    void* storage = componentStorage(enttRegistry, hash);
    return storage ? componentOf(storage, entity, size) : nullptr;
}

bool attributeValue(const AttributesComponent& attributes, std::uint32_t id, float& current, float& max) {
    const auto count = static_cast<std::size_t>(attributes.keys.last - attributes.keys.first);
    if (static_cast<std::size_t>(attributes.values.last - attributes.values.first) != count * size::AttributeInstance) {
        return false;
    }
    for (std::size_t i = 0; i < count; ++i) {
        if (attributes.keys.first[i] == id) {
            const std::uint8_t* instance = attributes.values.first + i * size::AttributeInstance;
            std::memcpy(&max, instance + offset::AttributeInstanceMax, sizeof max);
            std::memcpy(&current, instance + offset::AttributeInstanceCurrent, sizeof current);
            return true;
        }
    }
    return false;
}

bool readCamera(ClientInstance* client, Camera& camera) {
    auto pointerAt = [](const void* object, std::size_t offset) {
        const void* value;
        std::memcpy(&value, static_cast<const char*>(object) + offset, sizeof value);
        return value;
    };
    const void* game = pointerAt(client, offset::ClientInstanceMinecraftGame);
    const void* renderer = game ? pointerAt(game, offset::MinecraftGameGameRenderer) : nullptr;
    const void* levelRenderer = pointerAt(client, offset::ClientInstanceLevelRenderer);
    const void* levelRendererPlayer = levelRenderer ? pointerAt(levelRenderer, offset::LevelRendererPlayer) : nullptr;
    if (!renderer || !levelRendererPlayer) {
        return false;
    }
    std::memcpy(camera.view, static_cast<const char*>(renderer) + offset::GameRendererViewMatrix, sizeof camera.view);
    std::memcpy(camera.projection, static_cast<const char*>(renderer) + offset::GameRendererProjectionMatrix,
                sizeof camera.projection);
    std::memcpy(&camera.origin, static_cast<const char*>(levelRendererPlayer) + offset::LevelRendererPlayerOrigin,
                sizeof camera.origin);
    return true;
}

float* worldMatrixTop(ClientInstance* client) {
    using detail::readU64;
    const std::uint64_t stack =
        reinterpret_cast<std::uintptr_t>(client) + offset::ClientInstanceCamera + offset::CameraWorldMatrixStack;
    const std::uint64_t map = readU64(stack + offset::MatrixStackMap);
    const std::uint64_t mapSize = readU64(stack + offset::MatrixStackMapSize);
    const std::uint64_t first = readU64(stack + offset::MatrixStackFirst);
    const std::uint64_t count = readU64(stack + offset::MatrixStackCount);
    if (map == 0 || count == 0 || mapSize == 0 || (mapSize & (mapSize - 1)) != 0) {
        return nullptr;
    }
    return reinterpret_cast<float*>(static_cast<std::uintptr_t>(readU64(map + ((first + count - 1) & (mapSize - 1)) * 8)));
}

void markWorldMatrixDirty(ClientInstance* client) {
    const bool dirty = true;
    std::memcpy(reinterpret_cast<char*>(client) + offset::ClientInstanceCamera + offset::CameraWorldMatrixStack +
                    offset::MatrixStackDirty,
                &dirty, sizeof dirty);
}

const ItemStack* armorItem(Actor* actor, std::size_t slot) {
    if (slot >= offset::ArmorContainerStacks) {
        return nullptr;
    }
    EntityContext* context = entityContext(actor);
    void* storage = componentStorage(context->enttRegistry, offset::ArmorComponentHash);
    void* element = storage ? componentOf(storage, context->entity, offset::ArmorComponentSize) : nullptr;
    const std::uint64_t container = element ? detail::readU64(reinterpret_cast<std::uintptr_t>(element) + 8) : 0;
    const std::uint64_t stacks = container ? detail::readU64(container + offset::ArmorContainerItems) : 0;
    return stacks ? reinterpret_cast<const ItemStack*>(static_cast<std::uintptr_t>(stacks + slot * offset::ItemStackSize))
                  : nullptr;
}

const void* actorField(Actor* actor, std::uint32_t hash, std::size_t size) {
    EntityContext* context = entityContext(actor);
    void* storage = context ? componentStorage(context->enttRegistry, hash) : nullptr;
    if (!storage) {
        return nullptr;
    }
    if (size == 0) {
        const std::int64_t dense = denseIndex(storage, context->entity);
        if (dense < 0 || dense % entt_layout::PayloadPage != 0) {
            return nullptr;
        }
        size = 1;
    }
    return componentOf(storage, context->entity, size);
}

float actorFloat(Actor* actor, std::uint32_t hash, std::size_t size, float fallback) {
    const void* field = actorField(actor, hash, size);
    float value = fallback;
    if (field) {
        std::memcpy(&value, field, sizeof value);
    }
    return value;
}

float fallDistance(Actor* actor) {
    return actorFloat(actor, typeHash("FallDistanceComponent"), component_size::FallDistance, 0.0f);
}

float movementSpeed(Actor* actor) {
    return actorFloat(actor, typeHash("MovementSpeedComponent"), component_size::MovementSpeed, 0.0f);
}

float airSpeed(Actor* actor) {
    return actorFloat(actor, typeHash("AirSpeedComponent"), component_size::AirSpeed, 0.0f);
}

float maxAutoStep(Actor* actor) {
    return actorFloat(actor, typeHash("MaxAutoStepComponent"), component_size::MaxAutoStep, 0.0f);
}

int gameType(Actor* actor) {
    const void* field = actorField(actor, typeHash("ActorGameTypeComponent"), component_size::ActorGameType);
    std::int32_t value = -1;
    if (field) {
        std::memcpy(&value, field, sizeof value);
    }
    return value;
}

std::uint64_t runtimeId(Actor* actor) {
    const void* field = actorField(actor, typeHash("RuntimeIDComponent"), component_size::RuntimeID);
    std::uint64_t value = 0;
    if (field) {
        std::memcpy(&value, field, sizeof value);
    }
    return value;
}

bool onGround(Actor* actor) {
    EntityContext* context = entityContext(actor);
    void* storage = context ? componentStorage(context->enttRegistry, typeHash("VerticalCollisionFlagComponent"))
                            : nullptr;
    return storage != nullptr && denseIndex(storage, context->entity) >= 0;
}

void* abilityAt(Actor* actor, ability::Index which) {
    if (static_cast<std::size_t>(which) >= ability::Count) {
        return nullptr;
    }
    EntityContext* context = entityContext(actor);
    void* storage = context ? componentStorage(context->enttRegistry, typeHash("AbilitiesComponent")) : nullptr;
    void* component = storage ? componentOf(storage, context->entity, 1) : nullptr;
    if (!component) {
        return nullptr;
    }
    return reinterpret_cast<char*>(component) + offset::AbilitiesInComponent +
           static_cast<std::size_t>(which) * offset::AbilitySize;
}

bool abilityFlag(Actor* actor, ability::Index which, bool fallback) {
    void* entry = abilityAt(actor, which);
    if (!entry) {
        return fallback;
    }
    std::uint32_t kind = 0;
    std::uint32_t value = 0;
    std::memcpy(&kind, reinterpret_cast<const char*>(entry) + ability::TypeOffset, sizeof kind);
    std::memcpy(&value, reinterpret_cast<const char*>(entry) + ability::ValueOffset, sizeof value);
    return kind == ability::Bool ? value != 0 : fallback;
}

float abilitySpeed(Actor* actor, ability::Index which, float fallback) {
    void* entry = abilityAt(actor, which);
    if (!entry) {
        return fallback;
    }
    std::uint32_t kind = 0;
    float value = 0.0f;
    std::memcpy(&kind, reinterpret_cast<const char*>(entry) + ability::TypeOffset, sizeof kind);
    std::memcpy(&value, reinterpret_cast<const char*>(entry) + ability::ValueOffset, sizeof value);
    return kind == ability::Float ? value : fallback;
}

bool setAbility(Actor* actor, ability::Index which, bool on) {
    void* entry = abilityAt(actor, which);
    if (!entry) {
        return false;
    }
    std::uint32_t kind = 0;
    std::memcpy(&kind, reinterpret_cast<const char*>(entry) + ability::TypeOffset, sizeof kind);
    if (kind != ability::Bool) {
        return false;
    }
    const std::uint32_t value = on ? 1u : 0u;
    std::memcpy(reinterpret_cast<char*>(entry) + ability::ValueOffset, &value, sizeof value);
    return true;
}

bool setAbilitySpeed(Actor* actor, ability::Index which, float speed) {
    void* entry = abilityAt(actor, which);
    if (!entry) {
        return false;
    }
    std::uint32_t kind = 0;
    std::memcpy(&kind, reinterpret_cast<const char*>(entry) + ability::TypeOffset, sizeof kind);
    if (kind != ability::Float) {
        return false;
    }
    std::memcpy(reinterpret_cast<char*>(entry) + ability::ValueOffset, &speed, sizeof speed);
    return true;
}

void* playerInventory(Actor* actor) {
    return reinterpret_cast<void*>(
        static_cast<std::uintptr_t>(detail::readU64(reinterpret_cast<std::uintptr_t>(actor) + offset::PlayerSupplies)));
}

void* inventoryContainer(void* inventory) {
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(
        detail::readU64(reinterpret_cast<std::uintptr_t>(inventory) + offset::PlayerInventoryContainer)));
}

std::uint8_t selectedContainer(void* inventory) {
    std::uint8_t container = 0;
    std::memcpy(&container, reinterpret_cast<const char*>(inventory) + offset::PlayerInventorySelectedContainer,
                sizeof container);
    return container;
}

int selectedSlot(void* inventory) {
    int slot = 0;
    std::memcpy(&slot, reinterpret_cast<const char*>(inventory) + offset::PlayerInventorySelectedSlot, sizeof slot);
    return slot;
}

const void* itemBlock(const ItemStack* stack) {
    const std::uint64_t counter = detail::readU64(reinterpret_cast<std::uintptr_t>(stack) + offset::ItemStackItem);
    const std::uint64_t item = counter ? detail::readU64(counter) : 0;
    const std::uint64_t block = item ? detail::readU64(item + offset::ItemBlock) : 0;
    return reinterpret_cast<const void*>(static_cast<std::uintptr_t>(block));
}

int itemMaxDamage(const ItemStack* stack) {
    const std::uint64_t counter = detail::readU64(reinterpret_cast<std::uintptr_t>(stack) + offset::ItemStackItem);
    const std::uint64_t item = counter ? detail::readU64(counter) : 0;
    if (item == 0) {
        return 0;
    }
    std::int16_t maximum = 0;
    std::memcpy(&maximum, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(item + offset::ItemMaxDamage)),
                sizeof maximum);
    return maximum;
}

int itemDamage(const ItemStack* stack) {
    const std::uint64_t compound =
        detail::readU64(reinterpret_cast<std::uintptr_t>(stack) + offset::ItemStackTag);
    const std::uint64_t head = compound ? detail::readU64(compound + offset::TagCompoundMap) : 0;
    const std::uint64_t root = head ? detail::readU64(head + offset::TagMapRoot) : 0;
    std::uint64_t pending[offset::TagsWalked]{};
    std::size_t count = 0;
    if (root) {
        pending[count++] = root;
    }
    for (std::size_t seen = 0; count > 0 && seen < offset::TagsWalked; ++seen) {
        const std::uint64_t node = pending[--count];
        std::uint8_t nil = 1;
        std::memcpy(&nil, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(node + offset::TagNodeNil)), 1);
        if (nil == 1) {
            continue;
        }
        if (reinterpret_cast<const MsvcString*>(static_cast<std::uintptr_t>(node + offset::TagNodeKey))->view() == "Damage") {
            std::int32_t damage = 0;
            std::memcpy(&damage,
                        reinterpret_cast<const void*>(
                            static_cast<std::uintptr_t>(node + offset::TagNodeValue + offset::TagIntValue)),
                        sizeof damage);
            return damage;
        }
        for (const std::size_t child : {offset::TagNodeLeft, offset::TagNodeRight}) {
            const std::uint64_t following = detail::readU64(node + child);
            if (following && count < offset::TagsWalked) {
                pending[count++] = following;
            }
        }
    }
    return 0;
}

std::string_view itemName(const ItemStack* stack) {
    const std::uint64_t counter = detail::readU64(reinterpret_cast<std::uintptr_t>(stack) + offset::ItemStackItem);
    const std::uint64_t item = counter ? detail::readU64(counter) : 0;
    if (item == 0) {
        return {};
    }
    return reinterpret_cast<const MsvcString*>(static_cast<std::uintptr_t>(item + offset::ItemName))->view();
}

int itemCount(const ItemStack* stack) {
    return *(reinterpret_cast<const std::uint8_t*>(stack) + offset::ItemStackCount);
}

const ItemStack* itemActorStack(Actor* actor, std::uintptr_t moduleBase) {
    const std::uint64_t stack = reinterpret_cast<std::uintptr_t>(actor) + offset::ItemActorItemStack;
    if (detail::readU64(stack) != moduleBase + rva::ItemStackVtable) {
        return nullptr;
    }
    return reinterpret_cast<const ItemStack*>(static_cast<std::uintptr_t>(stack));
}

float* attackAnim(Actor* actor) {
    return reinterpret_cast<float*>(reinterpret_cast<char*>(actor) + offset::ActorAttackAnim);
}

float* attackAnimOld(Actor* actor) {
    return reinterpret_cast<float*>(reinterpret_cast<char*>(actor) + offset::ActorAttackAnimOld);
}

void* hitResultOf(Actor* actor) {
    EntityContext* context = entityContext(actor);
    void* component = context ? tryGetComponentRaw(context->enttRegistry, context->entity,
                                                   typeHash("HitResultComponent"), offset::HitResultComponentSize)
                              : nullptr;
    const std::uint64_t held = component ? detail::readU64(reinterpret_cast<std::uintptr_t>(component)) : 0;
    const std::uint64_t result = held ? detail::readU64(held + offset::HitResultInComponent) : 0;
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(result));
}

bool hitResult(Actor* actor, HitType& type, std::uint32_t& entity) {
    const std::uint64_t result = reinterpret_cast<std::uintptr_t>(hitResultOf(actor));
    if (result == 0) {
        return false;
    }
    std::int32_t raw;
    std::memcpy(&raw, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(result + offset::HitResultType)),
                sizeof raw);
    if (raw < static_cast<std::int32_t>(HitType::Block) || raw > static_cast<std::int32_t>(HitType::Air)) {
        return false;
    }
    type = static_cast<HitType>(raw);
    std::memcpy(&entity, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(result + offset::HitResultEntity)),
                sizeof entity);
    return true;
}

float renderPartialTick(ClientInstance* client) {
    using detail::readU64;
    const std::uint64_t owner = readU64(reinterpret_cast<std::uintptr_t>(client) + offset::ClientInstanceTimerOwner);
    const std::uint64_t timer = owner ? readU64(owner + offset::TimerOwnerTimer) : 0;
    if (timer == 0) {
        return 0.0f;
    }
    float partialTick;
    std::memcpy(&partialTick, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(timer + offset::TimerPartialTick)),
                sizeof partialTick);
    return partialTick;
}

bool cursorGrabbed(ClientInstance* client) {
    const std::uint64_t game = detail::readU64(reinterpret_cast<std::uintptr_t>(client) + offset::ClientInstanceMinecraftGame);
    if (game == 0) {
        return false;
    }
    std::uint8_t grabbed;
    std::memcpy(&grabbed, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(game + offset::MinecraftGameCursorGrabbed)),
                sizeof grabbed);
    return grabbed != 0;
}

}
