/** File:   nativeEvent_type.hpp
 * Author: sg
 * Created on 4. Mai 2017, 12:28 */

#ifndef NATIVEEVENT_TYPE_HPP
#define NATIVEEVENT_TYPE_HPP

#ifdef __linux__ //TODO: change to ifdef POSIX
  #include <OperatingSystem/POSIX/multithread/Event.hpp>
  typedef pthread::Condition nativeEvent_type;
#endif

#endif /* NATIVEEVENT_TYPE_HPP */
