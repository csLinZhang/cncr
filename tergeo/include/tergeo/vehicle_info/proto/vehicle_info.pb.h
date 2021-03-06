// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tergeo/vehicle_info/proto/vehicle_info.proto

#ifndef PROTOBUF_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto__INCLUDED
#define PROTOBUF_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace tergeo {
namespace vehicle_info {
namespace proto {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto();
void protobuf_AssignDesc_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto();
void protobuf_ShutdownFile_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto();

class VehicleInfoConfig;

// ===================================================================

class VehicleInfoConfig : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tergeo.vehicle_info.proto.VehicleInfoConfig) */ {
 public:
  VehicleInfoConfig();
  virtual ~VehicleInfoConfig();

  VehicleInfoConfig(const VehicleInfoConfig& from);

  inline VehicleInfoConfig& operator=(const VehicleInfoConfig& from) {
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
  static const VehicleInfoConfig& default_instance();

  void Swap(VehicleInfoConfig* other);

  // implements Message ----------------------------------------------

  inline VehicleInfoConfig* New() const { return New(NULL); }

  VehicleInfoConfig* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VehicleInfoConfig& from);
  void MergeFrom(const VehicleInfoConfig& from);
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
  void InternalSwap(VehicleInfoConfig* other);
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

  // required string vehicle_id = 1;
  bool has_vehicle_id() const;
  void clear_vehicle_id();
  static const int kVehicleIdFieldNumber = 1;
  const ::std::string& vehicle_id() const;
  void set_vehicle_id(const ::std::string& value);
  void set_vehicle_id(const char* value);
  void set_vehicle_id(const char* value, size_t size);
  ::std::string* mutable_vehicle_id();
  ::std::string* release_vehicle_id();
  void set_allocated_vehicle_id(::std::string* vehicle_id);

  // @@protoc_insertion_point(class_scope:tergeo.vehicle_info.proto.VehicleInfoConfig)
 private:
  inline void set_has_vehicle_id();
  inline void clear_has_vehicle_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr vehicle_id_;
  friend void  protobuf_AddDesc_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto();
  friend void protobuf_AssignDesc_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto();
  friend void protobuf_ShutdownFile_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto();

  void InitAsDefaultInstance();
  static VehicleInfoConfig* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// VehicleInfoConfig

// required string vehicle_id = 1;
inline bool VehicleInfoConfig::has_vehicle_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void VehicleInfoConfig::set_has_vehicle_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void VehicleInfoConfig::clear_has_vehicle_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void VehicleInfoConfig::clear_vehicle_id() {
  vehicle_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_vehicle_id();
}
inline const ::std::string& VehicleInfoConfig::vehicle_id() const {
  // @@protoc_insertion_point(field_get:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
  return vehicle_id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VehicleInfoConfig::set_vehicle_id(const ::std::string& value) {
  set_has_vehicle_id();
  vehicle_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
}
inline void VehicleInfoConfig::set_vehicle_id(const char* value) {
  set_has_vehicle_id();
  vehicle_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
}
inline void VehicleInfoConfig::set_vehicle_id(const char* value, size_t size) {
  set_has_vehicle_id();
  vehicle_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
}
inline ::std::string* VehicleInfoConfig::mutable_vehicle_id() {
  set_has_vehicle_id();
  // @@protoc_insertion_point(field_mutable:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
  return vehicle_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* VehicleInfoConfig::release_vehicle_id() {
  // @@protoc_insertion_point(field_release:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
  clear_has_vehicle_id();
  return vehicle_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void VehicleInfoConfig::set_allocated_vehicle_id(::std::string* vehicle_id) {
  if (vehicle_id != NULL) {
    set_has_vehicle_id();
  } else {
    clear_has_vehicle_id();
  }
  vehicle_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), vehicle_id);
  // @@protoc_insertion_point(field_set_allocated:tergeo.vehicle_info.proto.VehicleInfoConfig.vehicle_id)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace vehicle_info
}  // namespace tergeo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_tergeo_2fvehicle_5finfo_2fproto_2fvehicle_5finfo_2eproto__INCLUDED
