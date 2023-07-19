// Generated by gencpp from file rtabmap_msgs/CleanupLocalGridsResponse.msg
// DO NOT EDIT!


#ifndef RTABMAP_MSGS_MESSAGE_CLEANUPLOCALGRIDSRESPONSE_H
#define RTABMAP_MSGS_MESSAGE_CLEANUPLOCALGRIDSRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rtabmap_msgs
{
template <class ContainerAllocator>
struct CleanupLocalGridsResponse_
{
  typedef CleanupLocalGridsResponse_<ContainerAllocator> Type;

  CleanupLocalGridsResponse_()
    : modified(0)  {
    }
  CleanupLocalGridsResponse_(const ContainerAllocator& _alloc)
    : modified(0)  {
  (void)_alloc;
    }



   typedef int32_t _modified_type;
  _modified_type modified;





  typedef boost::shared_ptr< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> const> ConstPtr;

}; // struct CleanupLocalGridsResponse_

typedef ::rtabmap_msgs::CleanupLocalGridsResponse_<std::allocator<void> > CleanupLocalGridsResponse;

typedef boost::shared_ptr< ::rtabmap_msgs::CleanupLocalGridsResponse > CleanupLocalGridsResponsePtr;
typedef boost::shared_ptr< ::rtabmap_msgs::CleanupLocalGridsResponse const> CleanupLocalGridsResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator1> & lhs, const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator2> & rhs)
{
  return lhs.modified == rhs.modified;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator1> & lhs, const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace rtabmap_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "0079be4fbca49cb5090f065d768dbb2c";
  }

  static const char* value(const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x0079be4fbca49cb5ULL;
  static const uint64_t static_value2 = 0x090f065d768dbb2cULL;
};

template<class ContainerAllocator>
struct DataType< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rtabmap_msgs/CleanupLocalGridsResponse";
  }

  static const char* value(const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# return the number of grids or scans modified, -1 if there is an error\n"
"int32 modified\n"
"\n"
;
  }

  static const char* value(const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.modified);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct CleanupLocalGridsResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rtabmap_msgs::CleanupLocalGridsResponse_<ContainerAllocator>& v)
  {
    s << indent << "modified: ";
    Printer<int32_t>::stream(s, indent + "  ", v.modified);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RTABMAP_MSGS_MESSAGE_CLEANUPLOCALGRIDSRESPONSE_H