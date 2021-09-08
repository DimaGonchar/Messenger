// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Server.proto

#include "Server.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr ProtoServer::ProtoServer(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : responce_(0)
{}
struct ProtoServerDefaultTypeInternal {
  constexpr ProtoServerDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ProtoServerDefaultTypeInternal() {}
  union {
    ProtoServer _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ProtoServerDefaultTypeInternal _ProtoServer_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Server_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_Server_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Server_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Server_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::ProtoServer, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ProtoServer, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ProtoServer, responce_),
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 6, sizeof(::ProtoServer)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_ProtoServer_default_instance_),
};

const char descriptor_table_protodef_Server_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014Server.proto\"\213\002\n\013ProtoServer\022,\n\010respon"
  "ce\030\001 \001(\0162\025.ProtoServer.ResponseH\000\210\001\001\"\300\001\n"
  "\010Response\022\021\n\rUNKNOWN_ERROR\020\000\022\017\n\013USER_EXI"
  "STS\020\001\022\022\n\016USER_NOT_FOUND\020\002\022\024\n\020NO_CORRECT_"
  "LOGIN\020\003\022\023\n\017NO_CORRECT_PASS\020\004\022\035\n\031REGISTRA"
  "TION_IS_SUCCESFUL\020\005\022\036\n\032AUTHORIZATION_IS_"
  "SUCCESFUL\020\006\022\022\n\016USER_LOGGED_IN\020\007B\013\n\t_resp"
  "onceb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Server_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Server_2eproto = {
  false, false, 292, descriptor_table_protodef_Server_2eproto, "Server.proto", 
  &descriptor_table_Server_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_Server_2eproto::offsets,
  file_level_metadata_Server_2eproto, file_level_enum_descriptors_Server_2eproto, file_level_service_descriptors_Server_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_Server_2eproto_getter() {
  return &descriptor_table_Server_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_Server_2eproto(&descriptor_table_Server_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ProtoServer_Response_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Server_2eproto);
  return file_level_enum_descriptors_Server_2eproto[0];
}
bool ProtoServer_Response_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ProtoServer_Response ProtoServer::UNKNOWN_ERROR;
constexpr ProtoServer_Response ProtoServer::USER_EXISTS;
constexpr ProtoServer_Response ProtoServer::USER_NOT_FOUND;
constexpr ProtoServer_Response ProtoServer::NO_CORRECT_LOGIN;
constexpr ProtoServer_Response ProtoServer::NO_CORRECT_PASS;
constexpr ProtoServer_Response ProtoServer::REGISTRATION_IS_SUCCESFUL;
constexpr ProtoServer_Response ProtoServer::AUTHORIZATION_IS_SUCCESFUL;
constexpr ProtoServer_Response ProtoServer::USER_LOGGED_IN;
constexpr ProtoServer_Response ProtoServer::Response_MIN;
constexpr ProtoServer_Response ProtoServer::Response_MAX;
constexpr int ProtoServer::Response_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

class ProtoServer::_Internal {
 public:
  using HasBits = decltype(std::declval<ProtoServer>()._has_bits_);
  static void set_has_responce(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

ProtoServer::ProtoServer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ProtoServer)
}
ProtoServer::ProtoServer(const ProtoServer& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  responce_ = from.responce_;
  // @@protoc_insertion_point(copy_constructor:ProtoServer)
}

void ProtoServer::SharedCtor() {
responce_ = 0;
}

ProtoServer::~ProtoServer() {
  // @@protoc_insertion_point(destructor:ProtoServer)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ProtoServer::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ProtoServer::ArenaDtor(void* object) {
  ProtoServer* _this = reinterpret_cast< ProtoServer* >(object);
  (void)_this;
}
void ProtoServer::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ProtoServer::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ProtoServer::Clear() {
// @@protoc_insertion_point(message_clear_start:ProtoServer)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  responce_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ProtoServer::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .ProtoServer.Response responce = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_responce(static_cast<::ProtoServer_Response>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ProtoServer::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoServer)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .ProtoServer.Response responce = 1;
  if (_internal_has_responce()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_responce(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoServer)
  return target;
}

size_t ProtoServer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ProtoServer)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional .ProtoServer.Response responce = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_responce());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ProtoServer::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ProtoServer::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ProtoServer::GetClassData() const { return &_class_data_; }

void ProtoServer::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<ProtoServer *>(to)->MergeFrom(
      static_cast<const ProtoServer &>(from));
}


void ProtoServer::MergeFrom(const ProtoServer& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ProtoServer)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_responce()) {
    _internal_set_responce(from._internal_responce());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ProtoServer::CopyFrom(const ProtoServer& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ProtoServer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProtoServer::IsInitialized() const {
  return true;
}

void ProtoServer::InternalSwap(ProtoServer* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(responce_, other->responce_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ProtoServer::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Server_2eproto_getter, &descriptor_table_Server_2eproto_once,
      file_level_metadata_Server_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ProtoServer* Arena::CreateMaybeMessage< ::ProtoServer >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ProtoServer >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>