// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tergeo/adapter/proto/adapter_config.proto

#ifndef PROTOBUF_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto__INCLUDED
#define PROTOBUF_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace tergeo {
namespace adapter {
namespace proto {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
void protobuf_AssignDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
void protobuf_ShutdownFile_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();

class AdapterManagerConfig;
class ServiceAdapterConfig;
class TopicAdapterConfig;

enum AdapterMode {
  RECEIVE_ONLY = 0,
  PUBLISH_ONLY = 1,
  DUPLEX = 2
};
bool AdapterMode_IsValid(int value);
const AdapterMode AdapterMode_MIN = RECEIVE_ONLY;
const AdapterMode AdapterMode_MAX = DUPLEX;
const int AdapterMode_ARRAYSIZE = AdapterMode_MAX + 1;

const ::google::protobuf::EnumDescriptor* AdapterMode_descriptor();
inline const ::std::string& AdapterMode_Name(AdapterMode value) {
  return ::google::protobuf::internal::NameOfEnum(
    AdapterMode_descriptor(), value);
}
inline bool AdapterMode_Parse(
    const ::std::string& name, AdapterMode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AdapterMode>(
    AdapterMode_descriptor(), name, value);
}
// ===================================================================

class TopicAdapterConfig : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tergeo.adapter.proto.TopicAdapterConfig) */ {
 public:
  TopicAdapterConfig();
  virtual ~TopicAdapterConfig();

  TopicAdapterConfig(const TopicAdapterConfig& from);

  inline TopicAdapterConfig& operator=(const TopicAdapterConfig& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TopicAdapterConfig& default_instance();

  void Swap(TopicAdapterConfig* other);

  // implements Message ----------------------------------------------

  inline TopicAdapterConfig* New() const { return New(NULL); }

  TopicAdapterConfig* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TopicAdapterConfig& from);
  void MergeFrom(const TopicAdapterConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(TopicAdapterConfig* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional .tergeo.adapter.proto.AdapterMode mode = 2;
  bool has_mode() const;
  void clear_mode();
  static const int kModeFieldNumber = 2;
  ::tergeo::adapter::proto::AdapterMode mode() const;
  void set_mode(::tergeo::adapter::proto::AdapterMode value);

  // optional int64 message_history_limit = 3;
  bool has_message_history_limit() const;
  void clear_message_history_limit();
  static const int kMessageHistoryLimitFieldNumber = 3;
  ::google::protobuf::int64 message_history_limit() const;
  void set_message_history_limit(::google::protobuf::int64 value);

  // optional bool enable = 4;
  bool has_enable() const;
  void clear_enable();
  static const int kEnableFieldNumber = 4;
  bool enable() const;
  void set_enable(bool value);

  // @@protoc_insertion_point(class_scope:tergeo.adapter.proto.TopicAdapterConfig)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_mode();
  inline void clear_has_mode();
  inline void set_has_message_history_limit();
  inline void clear_has_message_history_limit();
  inline void set_has_enable();
  inline void clear_has_enable();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int64 message_history_limit_;
  int mode_;
  bool enable_;
  friend void  protobuf_AddDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
  friend void protobuf_AssignDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
  friend void protobuf_ShutdownFile_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();

  void InitAsDefaultInstance();
  static TopicAdapterConfig* default_instance_;
};
// -------------------------------------------------------------------

class ServiceAdapterConfig : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tergeo.adapter.proto.ServiceAdapterConfig) */ {
 public:
  ServiceAdapterConfig();
  virtual ~ServiceAdapterConfig();

  ServiceAdapterConfig(const ServiceAdapterConfig& from);

  inline ServiceAdapterConfig& operator=(const ServiceAdapterConfig& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ServiceAdapterConfig& default_instance();

  void Swap(ServiceAdapterConfig* other);

  // implements Message ----------------------------------------------

  inline ServiceAdapterConfig* New() const { return New(NULL); }

  ServiceAdapterConfig* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ServiceAdapterConfig& from);
  void MergeFrom(const ServiceAdapterConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ServiceAdapterConfig* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional .tergeo.adapter.proto.AdapterMode mode = 2;
  bool has_mode() const;
  void clear_mode();
  static const int kModeFieldNumber = 2;
  ::tergeo::adapter::proto::AdapterMode mode() const;
  void set_mode(::tergeo::adapter::proto::AdapterMode value);

  // optional bool enable = 3;
  bool has_enable() const;
  void clear_enable();
  static const int kEnableFieldNumber = 3;
  bool enable() const;
  void set_enable(bool value);

  // @@protoc_insertion_point(class_scope:tergeo.adapter.proto.ServiceAdapterConfig)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_mode();
  inline void clear_has_mode();
  inline void set_has_enable();
  inline void clear_has_enable();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  int mode_;
  bool enable_;
  friend void  protobuf_AddDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
  friend void protobuf_AssignDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
  friend void protobuf_ShutdownFile_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();

  void InitAsDefaultInstance();
  static ServiceAdapterConfig* default_instance_;
};
// -------------------------------------------------------------------

class AdapterManagerConfig : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tergeo.adapter.proto.AdapterManagerConfig) */ {
 public:
  AdapterManagerConfig();
  virtual ~AdapterManagerConfig();

  AdapterManagerConfig(const AdapterManagerConfig& from);

  inline AdapterManagerConfig& operator=(const AdapterManagerConfig& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AdapterManagerConfig& default_instance();

  void Swap(AdapterManagerConfig* other);

  // implements Message ----------------------------------------------

  inline AdapterManagerConfig* New() const { return New(NULL); }

  AdapterManagerConfig* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AdapterManagerConfig& from);
  void MergeFrom(const AdapterManagerConfig& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(AdapterManagerConfig* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .tergeo.adapter.proto.TopicAdapterConfig topic_config = 1;
  int topic_config_size() const;
  void clear_topic_config();
  static const int kTopicConfigFieldNumber = 1;
  const ::tergeo::adapter::proto::TopicAdapterConfig& topic_config(int index) const;
  ::tergeo::adapter::proto::TopicAdapterConfig* mutable_topic_config(int index);
  ::tergeo::adapter::proto::TopicAdapterConfig* add_topic_config();
  ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::TopicAdapterConfig >*
      mutable_topic_config();
  const ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::TopicAdapterConfig >&
      topic_config() const;

  // repeated .tergeo.adapter.proto.ServiceAdapterConfig service_config = 2;
  int service_config_size() const;
  void clear_service_config();
  static const int kServiceConfigFieldNumber = 2;
  const ::tergeo::adapter::proto::ServiceAdapterConfig& service_config(int index) const;
  ::tergeo::adapter::proto::ServiceAdapterConfig* mutable_service_config(int index);
  ::tergeo::adapter::proto::ServiceAdapterConfig* add_service_config();
  ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::ServiceAdapterConfig >*
      mutable_service_config();
  const ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::ServiceAdapterConfig >&
      service_config() const;

  // @@protoc_insertion_point(class_scope:tergeo.adapter.proto.AdapterManagerConfig)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::TopicAdapterConfig > topic_config_;
  ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::ServiceAdapterConfig > service_config_;
  friend void  protobuf_AddDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
  friend void protobuf_AssignDesc_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();
  friend void protobuf_ShutdownFile_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto();

  void InitAsDefaultInstance();
  static AdapterManagerConfig* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// TopicAdapterConfig

// optional string name = 1;
inline bool TopicAdapterConfig::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TopicAdapterConfig::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TopicAdapterConfig::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TopicAdapterConfig::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& TopicAdapterConfig::name() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.TopicAdapterConfig.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TopicAdapterConfig::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.TopicAdapterConfig.name)
}
inline void TopicAdapterConfig::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tergeo.adapter.proto.TopicAdapterConfig.name)
}
inline void TopicAdapterConfig::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tergeo.adapter.proto.TopicAdapterConfig.name)
}
inline ::std::string* TopicAdapterConfig::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:tergeo.adapter.proto.TopicAdapterConfig.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TopicAdapterConfig::release_name() {
  // @@protoc_insertion_point(field_release:tergeo.adapter.proto.TopicAdapterConfig.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TopicAdapterConfig::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tergeo.adapter.proto.TopicAdapterConfig.name)
}

// optional .tergeo.adapter.proto.AdapterMode mode = 2;
inline bool TopicAdapterConfig::has_mode() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TopicAdapterConfig::set_has_mode() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TopicAdapterConfig::clear_has_mode() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TopicAdapterConfig::clear_mode() {
  mode_ = 0;
  clear_has_mode();
}
inline ::tergeo::adapter::proto::AdapterMode TopicAdapterConfig::mode() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.TopicAdapterConfig.mode)
  return static_cast< ::tergeo::adapter::proto::AdapterMode >(mode_);
}
inline void TopicAdapterConfig::set_mode(::tergeo::adapter::proto::AdapterMode value) {
  assert(::tergeo::adapter::proto::AdapterMode_IsValid(value));
  set_has_mode();
  mode_ = value;
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.TopicAdapterConfig.mode)
}

// optional int64 message_history_limit = 3;
inline bool TopicAdapterConfig::has_message_history_limit() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TopicAdapterConfig::set_has_message_history_limit() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TopicAdapterConfig::clear_has_message_history_limit() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TopicAdapterConfig::clear_message_history_limit() {
  message_history_limit_ = GOOGLE_LONGLONG(0);
  clear_has_message_history_limit();
}
inline ::google::protobuf::int64 TopicAdapterConfig::message_history_limit() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.TopicAdapterConfig.message_history_limit)
  return message_history_limit_;
}
inline void TopicAdapterConfig::set_message_history_limit(::google::protobuf::int64 value) {
  set_has_message_history_limit();
  message_history_limit_ = value;
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.TopicAdapterConfig.message_history_limit)
}

// optional bool enable = 4;
inline bool TopicAdapterConfig::has_enable() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TopicAdapterConfig::set_has_enable() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TopicAdapterConfig::clear_has_enable() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TopicAdapterConfig::clear_enable() {
  enable_ = false;
  clear_has_enable();
}
inline bool TopicAdapterConfig::enable() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.TopicAdapterConfig.enable)
  return enable_;
}
inline void TopicAdapterConfig::set_enable(bool value) {
  set_has_enable();
  enable_ = value;
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.TopicAdapterConfig.enable)
}

// -------------------------------------------------------------------

// ServiceAdapterConfig

// optional string name = 1;
inline bool ServiceAdapterConfig::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ServiceAdapterConfig::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ServiceAdapterConfig::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ServiceAdapterConfig::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& ServiceAdapterConfig::name() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.ServiceAdapterConfig.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ServiceAdapterConfig::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.ServiceAdapterConfig.name)
}
inline void ServiceAdapterConfig::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tergeo.adapter.proto.ServiceAdapterConfig.name)
}
inline void ServiceAdapterConfig::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tergeo.adapter.proto.ServiceAdapterConfig.name)
}
inline ::std::string* ServiceAdapterConfig::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:tergeo.adapter.proto.ServiceAdapterConfig.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ServiceAdapterConfig::release_name() {
  // @@protoc_insertion_point(field_release:tergeo.adapter.proto.ServiceAdapterConfig.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ServiceAdapterConfig::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tergeo.adapter.proto.ServiceAdapterConfig.name)
}

// optional .tergeo.adapter.proto.AdapterMode mode = 2;
inline bool ServiceAdapterConfig::has_mode() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ServiceAdapterConfig::set_has_mode() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ServiceAdapterConfig::clear_has_mode() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ServiceAdapterConfig::clear_mode() {
  mode_ = 0;
  clear_has_mode();
}
inline ::tergeo::adapter::proto::AdapterMode ServiceAdapterConfig::mode() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.ServiceAdapterConfig.mode)
  return static_cast< ::tergeo::adapter::proto::AdapterMode >(mode_);
}
inline void ServiceAdapterConfig::set_mode(::tergeo::adapter::proto::AdapterMode value) {
  assert(::tergeo::adapter::proto::AdapterMode_IsValid(value));
  set_has_mode();
  mode_ = value;
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.ServiceAdapterConfig.mode)
}

// optional bool enable = 3;
inline bool ServiceAdapterConfig::has_enable() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ServiceAdapterConfig::set_has_enable() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ServiceAdapterConfig::clear_has_enable() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ServiceAdapterConfig::clear_enable() {
  enable_ = false;
  clear_has_enable();
}
inline bool ServiceAdapterConfig::enable() const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.ServiceAdapterConfig.enable)
  return enable_;
}
inline void ServiceAdapterConfig::set_enable(bool value) {
  set_has_enable();
  enable_ = value;
  // @@protoc_insertion_point(field_set:tergeo.adapter.proto.ServiceAdapterConfig.enable)
}

// -------------------------------------------------------------------

// AdapterManagerConfig

// repeated .tergeo.adapter.proto.TopicAdapterConfig topic_config = 1;
inline int AdapterManagerConfig::topic_config_size() const {
  return topic_config_.size();
}
inline void AdapterManagerConfig::clear_topic_config() {
  topic_config_.Clear();
}
inline const ::tergeo::adapter::proto::TopicAdapterConfig& AdapterManagerConfig::topic_config(int index) const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.AdapterManagerConfig.topic_config)
  return topic_config_.Get(index);
}
inline ::tergeo::adapter::proto::TopicAdapterConfig* AdapterManagerConfig::mutable_topic_config(int index) {
  // @@protoc_insertion_point(field_mutable:tergeo.adapter.proto.AdapterManagerConfig.topic_config)
  return topic_config_.Mutable(index);
}
inline ::tergeo::adapter::proto::TopicAdapterConfig* AdapterManagerConfig::add_topic_config() {
  // @@protoc_insertion_point(field_add:tergeo.adapter.proto.AdapterManagerConfig.topic_config)
  return topic_config_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::TopicAdapterConfig >*
AdapterManagerConfig::mutable_topic_config() {
  // @@protoc_insertion_point(field_mutable_list:tergeo.adapter.proto.AdapterManagerConfig.topic_config)
  return &topic_config_;
}
inline const ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::TopicAdapterConfig >&
AdapterManagerConfig::topic_config() const {
  // @@protoc_insertion_point(field_list:tergeo.adapter.proto.AdapterManagerConfig.topic_config)
  return topic_config_;
}

// repeated .tergeo.adapter.proto.ServiceAdapterConfig service_config = 2;
inline int AdapterManagerConfig::service_config_size() const {
  return service_config_.size();
}
inline void AdapterManagerConfig::clear_service_config() {
  service_config_.Clear();
}
inline const ::tergeo::adapter::proto::ServiceAdapterConfig& AdapterManagerConfig::service_config(int index) const {
  // @@protoc_insertion_point(field_get:tergeo.adapter.proto.AdapterManagerConfig.service_config)
  return service_config_.Get(index);
}
inline ::tergeo::adapter::proto::ServiceAdapterConfig* AdapterManagerConfig::mutable_service_config(int index) {
  // @@protoc_insertion_point(field_mutable:tergeo.adapter.proto.AdapterManagerConfig.service_config)
  return service_config_.Mutable(index);
}
inline ::tergeo::adapter::proto::ServiceAdapterConfig* AdapterManagerConfig::add_service_config() {
  // @@protoc_insertion_point(field_add:tergeo.adapter.proto.AdapterManagerConfig.service_config)
  return service_config_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::ServiceAdapterConfig >*
AdapterManagerConfig::mutable_service_config() {
  // @@protoc_insertion_point(field_mutable_list:tergeo.adapter.proto.AdapterManagerConfig.service_config)
  return &service_config_;
}
inline const ::google::protobuf::RepeatedPtrField< ::tergeo::adapter::proto::ServiceAdapterConfig >&
AdapterManagerConfig::service_config() const {
  // @@protoc_insertion_point(field_list:tergeo.adapter.proto.AdapterManagerConfig.service_config)
  return service_config_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace adapter
}  // namespace tergeo

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::tergeo::adapter::proto::AdapterMode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::tergeo::adapter::proto::AdapterMode>() {
  return ::tergeo::adapter::proto::AdapterMode_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_tergeo_2fadapter_2fproto_2fadapter_5fconfig_2eproto__INCLUDED
