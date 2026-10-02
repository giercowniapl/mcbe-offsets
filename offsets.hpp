#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>

namespace mc {

inline constexpr std::uint32_t kPeTimestamp = 0x6AB54E37;
inline constexpr const char* kGameVersion = "1.26.5203.0";

bool isSupportedBuild(const std::uint8_t* base);

namespace rva {
inline constexpr std::uintptr_t ActorVtable = 0xE7CAA50;
inline constexpr std::uintptr_t MobVtable = 0xE6AF850;
inline constexpr std::uintptr_t PlayerVtable = 0xE6D4A90;
inline constexpr std::uintptr_t LocalPlayerVtable = 0xE8E1BC0;
inline constexpr std::uintptr_t RemotePlayerVtable = 0xE8E23B0;
inline constexpr std::uintptr_t ServerPlayerVtable = 0xE83C0E0;
inline constexpr std::uintptr_t SimulatedPlayerVtable = 0xE8EF0B0;
inline constexpr std::uintptr_t ClientInstanceVtable = 0xE9731B0;
inline constexpr std::uintptr_t LevelRendererPlayerVtable = 0xE8DE6B0;
inline constexpr std::uintptr_t ClientInstanceGetLocalPlayer = 0x5DAED30;
inline constexpr std::uintptr_t LocalPlayerTryGetFromEntity = 0x476E930;
inline constexpr std::uintptr_t ClientInstanceUpdate = 0x5DA7C00;
inline constexpr std::uintptr_t ClientInstanceGrabCursor = 0x5DCE3C0;
inline constexpr std::uintptr_t ClientInstanceReleaseCursor = 0x5DCE410;
inline constexpr std::uintptr_t GameCoreVtable = 0xE6A6380;
inline constexpr std::uintptr_t GameCoreHandleMouseInput = 0x8A880;
inline constexpr std::uintptr_t MouseDevice = 0x11D29E40;
inline constexpr std::uintptr_t ItemInHandRendererRenderItem = 0x47B5BA0;
inline constexpr std::uintptr_t ItemStackVtable = 0xE6D6CD0;
inline constexpr std::uintptr_t GameModeGetPickRange = 0x259F9E0;
inline constexpr std::uintptr_t GameModeGetPickRangeEntries[] = {0xE8275B0, 0xE827650};
inline constexpr std::uintptr_t LocalPlayerApplyTurnDelta = 0x4761890;
inline constexpr std::uintptr_t PlayerInventorySelectSlot = 0x1F4860;
inline constexpr std::uintptr_t ActorGetDimensionBlockSource = 0x19EA0B0;
inline constexpr std::uintptr_t ItemStackEmpty = 0x11D65D50;
inline constexpr std::uintptr_t BoneOrientationSetMatrix = 0x1BC3A30;
inline constexpr std::uintptr_t FontDrawText = 0x4447210;
inline constexpr std::uintptr_t FontDrawTextEntries[] = {0xE7B9F70, 0xE8CFF80, 0xE8D0F30, 0xE8D1030, 0xE905970, 0xE905AA0};
inline constexpr std::uintptr_t FontTextWidth = 0x4443BC0;
inline constexpr std::uintptr_t FontTextWidthEntries[] = {0xE7B9F80, 0xE8CFF90, 0xE8D0F40, 0xE8D1040, 0xE905980, 0xE905AB0};
inline constexpr std::uintptr_t GameModeAttack = 0x2599CB0;
inline constexpr std::uintptr_t MovementSendSystem = 0x4769770;
inline constexpr std::uintptr_t PlayerAuthInputPacketVtable = 0xE83A360;
inline constexpr std::uintptr_t NametagPass = 0x46BA370;
inline constexpr std::uintptr_t DrawNametag = 0x1F122D0;
inline constexpr std::uintptr_t ItemStackNetManagerBeginRequest = 0x25B0750;
inline constexpr std::uintptr_t ItemStackNetManagerAddRequestAction = 0x25B1EF0;
inline constexpr std::uintptr_t ItemStackNetManagerEndRequest = 0x25B0BF0;
inline constexpr std::uintptr_t ItemStackRequestIdCounter = 0x11D68B7C;
}

namespace prologue {
inline constexpr std::uint8_t ItemInHandRendererRenderItem[] = {0x55, 0x41, 0x57, 0x41, 0x56};
inline constexpr std::uint8_t BoneOrientationSetMatrix[] = {0x48, 0x83, 0xEC, 0x68, 0x44, 0x0F, 0x29, 0x5C, 0x24, 0x50};
inline constexpr std::uint8_t GameModeAttack[] = {0x55, 0x41, 0x57, 0x41, 0x56};
inline constexpr std::uint8_t GameModeAttackOpening[] = {0x55, 0x41, 0x57, 0x41, 0x56, 0x41, 0x55, 0x41, 0x54, 0x56,
                                                         0x57, 0x53, 0x48, 0x81, 0xEC, 0xF8, 0x01, 0x00, 0x00};
inline constexpr std::uint8_t MovementSendSystem[] = {0x55, 0x41, 0x57, 0x41, 0x56};
inline constexpr std::uint8_t MovementSendSystemOpening[] = {0x55, 0x41, 0x57, 0x41, 0x56, 0x41, 0x55, 0x41, 0x54, 0x56,
                                                             0x57, 0x53, 0x48, 0x81, 0xEC, 0x98, 0x01, 0x00, 0x00};
inline constexpr std::uint8_t NametagPassCode[] = {
    0x41, 0x57, 0x41, 0x56, 0x41, 0x54, 0x56, 0x57, 0x53, 0x48, 0x83, 0xEC, 0x28, 0x4D, 0x8B, 0xB8, 0xE8, 0x32, 0x00,
    0x00, 0x4D, 0x8B, 0xA0, 0xF0, 0x32, 0x00, 0x00, 0x4D, 0x39, 0xE7, 0x74, 0x40, 0x4C, 0x89, 0xCE, 0x4C, 0x89, 0xC7,
    0x48, 0x89, 0xD3, 0x49, 0x89, 0xCE, 0x0F, 0x1F, 0x40, 0x00, 0x49, 0x8B, 0x86, 0x88, 0x11, 0x00, 0x00, 0x48, 0x8B,
    0x80, 0xB0, 0x01, 0x00, 0x00, 0x48, 0x89, 0x44, 0x24, 0x20, 0x48, 0x89, 0xD9, 0x48, 0x89, 0xFA, 0x4D, 0x89, 0xF8,
    0x49, 0x89, 0xF1, 0xE8, 0x0C, 0x7F, 0x85, 0xFD, 0x49, 0x81, 0xC7, 0x90, 0x00, 0x00, 0x00, 0x4D, 0x39, 0xE7, 0x75,
    0xD0, 0x48, 0x83, 0xC4, 0x28, 0x5B, 0x5F, 0x5E, 0x41, 0x5C, 0x41, 0x5E, 0x41, 0x5F, 0xC3};
}

namespace slot {
inline constexpr std::size_t ClientInstanceGetLocalPlayer = 31;
inline constexpr std::size_t ClientInstanceUpdate = 24;
inline constexpr std::size_t ClientInstanceGrabCursor = 310;
inline constexpr std::size_t ClientInstanceReleaseCursor = 311;
inline constexpr std::size_t GameCoreHandleMouseInput = 2;
inline constexpr std::size_t PlayerGetCarriedItem = 77;
inline constexpr std::size_t ContainerGetItem = 7;
inline constexpr std::size_t BlockSourceGetBlock = 2;
inline constexpr std::size_t DimensionBlockSource = 12;
inline constexpr std::size_t GameModeBuildBlock = 6;
inline constexpr std::size_t GameModeGetPickRange = 10;
inline constexpr std::size_t PacketSenderSend = 2;
inline constexpr std::size_t LevelRendererPlayerNametagPass = 11;
}

namespace vtable_slots {
inline constexpr std::size_t Actor = 136;
inline constexpr std::size_t Mob = 174;
inline constexpr std::size_t Player = 245;
inline constexpr std::size_t LocalPlayer = 245;
inline constexpr std::size_t RemotePlayer = 245;
inline constexpr std::size_t ServerPlayer = 247;
inline constexpr std::size_t SimulatedPlayer = 247;
inline constexpr std::size_t ClientInstance = 422;
}

namespace offset {
inline constexpr std::size_t ClientInstanceLocalPlayerEntityRef = 0x248;
inline constexpr std::size_t ActorEntityContext = 0x8;
inline constexpr std::size_t MouseDeviceInputs = 0x18;
inline constexpr std::size_t ActorStateVectorPtr = 0x218;
inline constexpr std::size_t ActorAABBShapePtr = 0x220;
inline constexpr std::size_t ActorRotationPtr = 0x228;
inline constexpr std::size_t ActorWalkAnimationPtr = 0x230;
inline constexpr std::size_t ClientInstanceMinecraftGame = 0x1A8;
inline constexpr std::size_t MinecraftGameGameRenderer = 0x1440;
inline constexpr std::size_t GameRendererViewMatrix = 0x388;
inline constexpr std::size_t GameRendererProjectionMatrix = 0x408;
inline constexpr std::size_t ClientInstanceLevelRenderer = 0x1C0;
inline constexpr std::size_t LevelRendererPlayer = 0x468;
inline constexpr std::size_t LevelRendererPlayerOrigin = 0x660;
inline constexpr std::size_t MinecraftGameCursorGrabbed = 0x1E8;
inline constexpr std::size_t ActorDefinitionIdentifierName = 0x20;
inline constexpr std::size_t AttributeInstanceMax = 0x78;
inline constexpr std::size_t AttributeInstanceCurrent = 0x7C;
inline constexpr std::size_t ClientInstanceCamera = 0x360;
inline constexpr std::size_t CameraWorldMatrixStack = 0x40;
inline constexpr std::size_t MatrixStackMap = 0x8;
inline constexpr std::size_t MatrixStackMapSize = 0x10;
inline constexpr std::size_t MatrixStackFirst = 0x18;
inline constexpr std::size_t MatrixStackCount = 0x20;
inline constexpr std::size_t MatrixStackDirty = 0x38;
inline constexpr std::size_t ItemStackItem = 0x8;
inline constexpr std::size_t ItemName = 0xD8;
inline constexpr std::size_t ItemActorItemStack = 0x3B0;
inline constexpr std::size_t ItemStackCount = 0x22;
inline constexpr std::uint32_t ArmorComponentHash = 0xB06141A9;
inline constexpr std::size_t ArmorContainerItems = 0x1A0;
inline constexpr std::size_t ArmorContainerStacks = 5;
inline constexpr std::size_t ArmorSlots = 4;
inline constexpr std::size_t ItemStackSize = 0x98;
inline constexpr std::size_t ArmorComponentSize = 0x10;
inline constexpr std::size_t ItemMaxDamage = 0x150;
inline constexpr std::size_t ItemStackTag = 0x10;
inline constexpr std::size_t TagCompoundMap = 0x8;
inline constexpr std::size_t TagMapRoot = 0x8;
inline constexpr std::size_t TagNodeLeft = 0x0;
inline constexpr std::size_t TagNodeRight = 0x10;
inline constexpr std::size_t TagNodeNil = 0x19;
inline constexpr std::size_t TagNodeKey = 0x20;
inline constexpr std::size_t TagNodeValue = 0x40;
inline constexpr std::size_t TagIntValue = 0x8;
inline constexpr std::size_t TagsWalked = 32;
inline constexpr std::size_t ActorAttackAnim = 0x40C;
inline constexpr std::size_t ActorSwingTick = 0x410;
inline constexpr std::size_t ActorSwinging = 0x434;
inline constexpr std::size_t ActorAttackAnimOld = 0x450;
inline constexpr std::size_t LocalPlayerGameMode = 0xAA0;
inline constexpr std::size_t SendSystemSender = 0x7F8;
inline constexpr std::size_t ClientInstanceTimerOwner = 0x1B0;
inline constexpr std::size_t TimerOwnerTimer = 0xE0;
inline constexpr std::size_t TimerPartialTick = 0x8;
inline constexpr std::size_t HitResultComponentSize = 0x30;
inline constexpr std::size_t HitResultInComponent = 0x8;
inline constexpr std::size_t HitResultRay = 0xC;
inline constexpr std::size_t HitResultType = 0x18;
inline constexpr std::size_t HitResultFacing = 0x1C;
inline constexpr std::size_t HitResultBlock = 0x20;
inline constexpr std::size_t HitResultPos = 0x2C;
inline constexpr std::size_t HitResultEntity = 0x48;
inline constexpr std::size_t PlayerName = 0xBC0;
inline constexpr std::size_t ActorAnimationComponent = 0x270;
inline constexpr std::size_t AnimationComponentBoneMap = 0x320;
inline constexpr std::size_t BoneMapNodeVector = 0x18;
inline constexpr std::size_t BoneOrientationNameHash = 0x8;
inline constexpr std::size_t BoneOrientationMatrix = 0x38;
inline constexpr std::size_t BoneOrientationPivot = 0xD8;
inline constexpr std::size_t PlayerSkin = 0xAB0;
inline constexpr std::size_t SerializedSkinGeometryName = 0x80;
inline constexpr std::size_t SerializedSkinImage = 0xA0;
inline constexpr std::size_t SerializedSkinCape = 0xD0;
inline constexpr std::size_t ImageFormat = 0x0;
inline constexpr std::size_t ImageWidth = 0x4;
inline constexpr std::size_t ImageHeight = 0x8;
inline constexpr std::size_t ImageBlobData = 0x20;
inline constexpr std::size_t ImageBlobSize = 0x28;
inline constexpr std::size_t PlayerSupplies = 0x5B8;
inline constexpr std::size_t PlayerInventorySelectedContainer = 0xB0;
inline constexpr std::size_t PlayerInventoryContainer = 0xB8;
inline constexpr std::size_t PlayerInventorySelectedSlot = 0x10;
inline constexpr std::size_t ItemBlock = 0x178;
inline constexpr std::size_t AbilitiesInComponent = 0x108;
inline constexpr std::size_t AbilitySize = 0xC;
inline constexpr std::size_t FrameNametags = 0x32E8;
inline constexpr std::size_t NametagSize = 0x90;
inline constexpr std::size_t NametagText = 0x0;
inline constexpr std::size_t NametagColor = 0x30;
inline constexpr std::size_t NametagPosition = 0x50;
inline constexpr std::size_t NametagPassFontOwner = 0x1188;
inline constexpr std::size_t FontInOwner = 0x1B0;
}

namespace auth_input {
inline constexpr std::size_t Rotation = 0x30;
inline constexpr std::size_t Position = 0x38;
inline constexpr std::size_t HeadRotation = 0x44;
inline constexpr std::size_t PosDelta = 0x48;
inline constexpr std::size_t VehicleRotation = 0x54;
inline constexpr std::size_t AnalogMove = 0x5C;
inline constexpr std::size_t Move = 0x64;
inline constexpr std::size_t InteractRotation = 0x6C;
inline constexpr std::size_t CameraOrientation = 0x74;
inline constexpr std::size_t RawMove = 0x80;
inline constexpr std::size_t InputData = 0x88;
inline constexpr std::size_t InputMode = 0x98;
inline constexpr std::size_t PlayMode = 0x9C;
inline constexpr std::size_t InteractionModel = 0xA0;
inline constexpr std::size_t ClientTick = 0xA8;

inline constexpr int Jumping = 6;
inline constexpr int StartJumping = 31;
}

namespace ability {
inline constexpr std::size_t Count = 20;
enum Index {
    Build = 0,
    Mine = 1,
    Doorsandswitches = 2,
    Opencontainers = 3,
    Attackplayers = 4,
    Attackmobs = 5,
    Op = 6,
    Teleport = 7,
    Invulnerable = 8,
    Flying = 9,
    Mayfly = 10,
    Instabuild = 11,
    Lightning = 12,
    FlySpeed = 13,
    WalkSpeed = 14,
    Mute = 15,
    Worldbuilder = 16,
    Noclip = 17,
    PrivilegedBuilder = 18,
    VerticalFlySpeed = 19,
};
inline constexpr std::uint32_t Bool = 2;
inline constexpr std::uint32_t Float = 3;
inline constexpr std::size_t TypeOffset = 0;
inline constexpr std::size_t ValueOffset = 4;
inline constexpr std::size_t OptionsOffset = 8;
}

namespace component_size {
inline constexpr std::size_t ActorGameType = 0;
inline constexpr std::size_t AirSpeed = 0;
inline constexpr std::size_t FallDistance = 0;
inline constexpr std::size_t MaxAutoStep = 0;
inline constexpr std::size_t MovementSpeed = 0;
inline constexpr std::size_t RuntimeID = 0x8;
inline constexpr std::size_t SwimSpeedMultiplier = 0;
inline constexpr std::size_t WalkDist = 0;
}

namespace image_format {
inline constexpr std::uint32_t Rgba8 = 4;
}

namespace block_face {
inline constexpr std::uint8_t Down = 0;
inline constexpr std::uint8_t Up = 1;
inline constexpr std::uint8_t North = 2;
inline constexpr std::uint8_t South = 3;
inline constexpr std::uint8_t West = 4;
inline constexpr std::uint8_t East = 5;
}

namespace size {
inline constexpr std::size_t StateVectorComponent = 0x24;
inline constexpr std::size_t AABBShapeComponent = 0x20;
inline constexpr std::size_t ActorRotationComponent = 0x10;
inline constexpr std::size_t ActorWalkAnimationComponent = 0x14;
inline constexpr std::size_t RenderPositionComponent = 0xC;
inline constexpr std::size_t BoneOrientation = 0xE8;
inline constexpr std::size_t ActorDefinitionIdentifierComponent = 0xB0;
inline constexpr std::size_t AttributesComponent = 0x50;
inline constexpr std::size_t AttributeInstance = 0x88;
inline constexpr std::size_t ActorTypeComponent = 0x4;
}

namespace entt_layout {
inline constexpr std::uint64_t RegistryBuckets = 0x48;
inline constexpr std::uint64_t RegistryNodes = 0x68;
inline constexpr std::uint64_t PoolNodeSize = 0x20;
inline constexpr std::uint64_t PoolNodeHash = 0x8;
inline constexpr std::uint64_t PoolNodeStorage = 0x10;
inline constexpr std::uint64_t StorageSparse = 0x8;
inline constexpr std::uint64_t StoragePayload = 0x50;
inline constexpr std::uint64_t StoragePacked = 0x20;
inline constexpr std::uint32_t SparsePage = 2048;
inline constexpr std::uint32_t PayloadPage = 128;
inline constexpr std::uint32_t EntityMask = 0x3FFFF;
}

namespace attribute {
inline constexpr std::uint32_t Health = 7;
}

namespace actor_type {
inline constexpr std::uint32_t ItemEntity = 0x40;
}

constexpr std::uint32_t typeHash(std::string_view name) {
    std::uint32_t hash = 2166136261u;
    for (char c : name) {
        hash ^= static_cast<std::uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}
static_assert(typeHash("ActorOwnerComponent") == 0x85B93800u);
static_assert(typeHash("LocalPlayerComponent") == 0xACB47B38u);
static_assert(typeHash("MobFlagComponent") == 0x14EA24A2u);
static_assert(typeHash("PlayerComponent") == 0xF95D258Fu);
static_assert(typeHash("RenderPositionComponent") == 0xE53C7221u);
static_assert(typeHash("AABBShapeComponent") == 0xBAC1B3CFu);
static_assert(typeHash("ActorDefinitionIdentifierComponent") == 0xDEB6534Fu);
static_assert(typeHash("AttributesComponent") == 0xFD3B0613u);
static_assert(typeHash("MonsterFlagComponent") == 0x6FA87086u);
static_assert(typeHash("ActorTypeComponent") == 0x4F6BA419u);
static_assert(typeHash("MobBodyRotationComponent") == 0xD7F64BBAu);
static_assert(typeHash("MobHurtTimeComponent") == 0xD7A3585Cu);

constexpr std::uint64_t boneNameHash(std::string_view name) {
    std::uint64_t hash = 0xCBF29CE484222325ull;
    for (const char c : name) {
        hash = (hash * 0x100000001B3ull) ^ static_cast<std::uint8_t>(c);
    }
    return hash;
}

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

struct StateVectorComponent { Vec3 pos; Vec3 posPrev; Vec3 posDelta; };
static_assert(sizeof(StateVectorComponent) == 0x24);

struct AABBShapeComponent { Vec3 min; Vec3 max; Vec2 size; };
static_assert(sizeof(AABBShapeComponent) == 0x20);

struct ActorRotationComponent { float pitch; float yaw; float prevPitch; float prevYaw; };
static_assert(sizeof(ActorRotationComponent) == 0x10);

struct ActorWalkAnimationComponent { float unknown; float prevSpeed; float speed; float position; float distance; };
static_assert(sizeof(ActorWalkAnimationComponent) == 0x14);

struct MobBodyRotationComponent { float yaw; float prevYaw; };
static_assert(sizeof(MobBodyRotationComponent) == 0x8);

struct MobHurtTimeComponent { std::int32_t ticks; };
static_assert(sizeof(MobHurtTimeComponent) == 0x4);

struct MouseAction {
    std::int16_t x, y, dx, dy;
    std::int8_t action;
    std::int8_t data;
    std::int32_t pointerId;
    bool forceMotionlessPointer;
};
static_assert(sizeof(MouseAction) == 0x14);

struct MouseActionVector { MouseAction* first; MouseAction* last; MouseAction* end; };
static_assert(sizeof(MouseActionVector) == 0x18);

struct RenderPositionComponent { Vec3 pos; };
static_assert(sizeof(RenderPositionComponent) == 0xC);

struct MsvcString {
    union {
        char inlineChars[16];
        const char* heapChars;
    };
    std::size_t size;
    std::size_t capacity;
    std::string_view view() const { return {capacity < 16 ? inlineChars : heapChars, size}; }
};
static_assert(sizeof(MsvcString) == 0x20);

struct MsvcStringView {
    const char* data;
    std::size_t size;
};
static_assert(sizeof(MsvcStringView) == 0x10);

template <class T>
struct MsvcVector {
    T* first;
    T* last;
    T* end;
};

struct AttributesComponent {
    MsvcVector<std::uint32_t> keys;
    MsvcVector<std::uint8_t> values;
    std::uint8_t rest[0x50 - 0x30];
};
static_assert(sizeof(AttributesComponent) == 0x50);

struct Camera {
    Vec3 origin;
    float view[16];
    float projection[16];
};

struct EntityContext {
    void* registry;
    void* enttRegistry;
    std::uint32_t entity;
};
static_assert(sizeof(EntityContext) == 0x18);

class Actor { public: Actor() = delete; };
class Mob : public Actor { public: Mob() = delete; };
class Player : public Mob { public: Player() = delete; };
class LocalPlayer : public Player { public: LocalPlayer() = delete; };
class RemotePlayer : public Player { public: RemotePlayer() = delete; };
class ServerPlayer : public Player { public: ServerPlayer() = delete; };
class SimulatedPlayer : public ServerPlayer { public: SimulatedPlayer() = delete; };
class ClientInstance { public: ClientInstance() = delete; };
class GameCore { public: GameCore() = delete; };
class GameMode;
class ItemInHandRenderer { public: ItemInHandRenderer() = delete; };
class ItemStack { public: ItemStack() = delete; };

using ClientInstanceUpdateFn = bool (*)(ClientInstance* client, bool arg);

using ClientInstanceCursorFn = void (*)(ClientInstance* client);

using GameCoreHandleMouseInputFn = void (*)(GameCore* core);

using ItemInHandRendererRenderItemFn = void* (*)(ItemInHandRenderer* renderer, void* context, Actor* actor,
                                                 ItemStack* item, std::uint8_t a5, std::uint8_t a6, std::uint8_t a7,
                                                 std::uint8_t a8);

using GameModeGetPickRangeFn = float (*)(GameMode* mode, const std::int32_t* inputMode, bool a3);

using GameModeAttackFn = void (*)(GameMode* gameMode, Actor* target, unsigned char flag, const Vec3* pos);

using GameModeBuildBlockFn = bool (*)(GameMode* gameMode, const std::int32_t* blockPos, char face, unsigned char mode,
                                      char check);

using MovementSendSystemFn = void (*)(void* context);

using PacketSenderSendFn = void (*)(void* sender, void* packet);

using NametagPassFn = void (*)(void* pass, void* screen, void* frame, void* extra);
using DrawNametagFn = void (*)(void* screen, void* frame, const std::uint8_t* tag, void* extra, void* font);

using BoneOrientationSetMatrixFn = char(__fastcall*)(void* record, const void* translation, void* matrix);

using FontDrawTextFn = std::uint64_t (*)(void* font, void* screen, const MsvcStringView* text, float x,
                                        std::uint64_t a5, std::uint64_t a6, std::uint64_t a7, std::uint64_t a8,
                                        std::uint64_t a9, std::uint64_t a10, std::uint64_t a11, std::uint64_t a12,
                                        std::uint64_t a13, std::uint64_t a14, std::uint64_t a15, std::uint64_t a16,
                                        std::uint64_t a17, std::uint64_t a18, std::uint64_t a19, std::uint64_t a20,
                                        std::uint64_t a21, std::uint64_t a22, std::uint64_t a23, std::uint64_t a24);

using FontTextWidthFn = std::uint64_t (*)(void* font, const MsvcStringView* text, std::uint64_t a3, std::uint64_t a4);

using PlayerInventorySelectSlotFn = bool (*)(void* inventory, int slot, std::uint8_t containerId);

using ContainerGetItemFn = const ItemStack* (*)(void* container, int slot);

using ActorGetDimensionBlockSourceFn = void* (*)(Actor* actor);
using BlockSourceGetBlockFn = const void* (*)(void* blockSource, const std::int32_t* pos);

namespace detail {
inline std::uint64_t readU64(std::uint64_t address) {
    std::uint64_t value;
    std::memcpy(&value, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(address)), sizeof value);
    return value;
}
inline std::uint32_t readU32(std::uint64_t address) {
    std::uint32_t value;
    std::memcpy(&value, reinterpret_cast<const void*>(static_cast<std::uintptr_t>(address)), sizeof value);
    return value;
}
}

LocalPlayer* getLocalPlayer(ClientInstance* client);

EntityContext* entityContext(Actor* actor);
StateVectorComponent* stateVector(Actor* actor);
AABBShapeComponent* aabbShape(Actor* actor);
ActorRotationComponent* rotation(Actor* actor);
ActorWalkAnimationComponent* walkAnimation(Actor* actor);

void* componentStorage(void* enttRegistry, std::uint32_t hash);

std::int64_t denseIndex(void* storage, std::uint32_t entity);

bool hasComponent(void* storage, std::uint32_t entity);

void* componentOf(void* storage, std::uint32_t entity, std::size_t size);

template <class Fn>
void forEachEntity(void* storage, Fn&& fn) {
    const std::uint64_t pool = reinterpret_cast<std::uintptr_t>(storage);
    const std::uint64_t packed = detail::readU64(pool + entt_layout::StoragePacked);
    const std::uint64_t packedEnd = detail::readU64(pool + entt_layout::StoragePacked + 8);
    for (std::uint64_t i = 0; packedEnd > packed && i < (packedEnd - packed) / 4; ++i) {
        const std::uint32_t entity = detail::readU32(packed + i * 4);
        if (denseIndex(storage, entity) == static_cast<std::int64_t>(i)) {
            fn(entity);
        }
    }
}

void* tryGetComponentRaw(void* enttRegistry, std::uint32_t entity, std::uint32_t hash, std::size_t size);

template <class T>
T* tryGetComponent(Actor* actor, std::string_view typeName) {
    EntityContext* context = entityContext(actor);
    return static_cast<T*>(tryGetComponentRaw(context->enttRegistry, context->entity, typeHash(typeName), sizeof(T)));
}

bool attributeValue(const AttributesComponent& attributes, std::uint32_t id, float& current, float& max);

bool readCamera(ClientInstance* client, Camera& camera);

float* worldMatrixTop(ClientInstance* client);

void markWorldMatrixDirty(ClientInstance* client);

const ItemStack* armorItem(Actor* actor, std::size_t slot);

const void* actorField(Actor* actor, std::uint32_t hash, std::size_t size);
float actorFloat(Actor* actor, std::uint32_t hash, std::size_t size, float fallback);

float fallDistance(Actor* actor);

float movementSpeed(Actor* actor);
float airSpeed(Actor* actor);

float maxAutoStep(Actor* actor);

int gameType(Actor* actor);

std::uint64_t runtimeId(Actor* actor);

bool onGround(Actor* actor);

void* abilityAt(Actor* actor, ability::Index which);

bool abilityFlag(Actor* actor, ability::Index which, bool fallback = false);

float abilitySpeed(Actor* actor, ability::Index which, float fallback = 0.0f);

bool setAbility(Actor* actor, ability::Index which, bool on);
bool setAbilitySpeed(Actor* actor, ability::Index which, float speed);

void* playerInventory(Actor* actor);

void* inventoryContainer(void* inventory);

std::uint8_t selectedContainer(void* inventory);

int selectedSlot(void* inventory);

const void* itemBlock(const ItemStack* stack);

int itemMaxDamage(const ItemStack* stack);

int itemDamage(const ItemStack* stack);

std::string_view itemName(const ItemStack* stack);

int itemCount(const ItemStack* stack);

const ItemStack* itemActorStack(Actor* actor, std::uintptr_t moduleBase);

float* attackAnim(Actor* actor);
float* attackAnimOld(Actor* actor);

enum class HitType : std::int32_t { Block, Entity, EntityOutOfRange, Air };

void* hitResultOf(Actor* actor);

bool hitResult(Actor* actor, HitType& type, std::uint32_t& entity);

float renderPartialTick(ClientInstance* client);

bool cursorGrabbed(ClientInstance* client);

}
