cmake_minimum_required(VERSION 2.8.3)
project(food_pager_center)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)



add_message_files(
   FILES
   Order.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES food_pager_center
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
  CATKIN_DEPENDS message_runtime
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(cashier src/cashier.cc)
target_link_libraries(cashier ${catkin_LIBRARIES})

add_executable(chef src/chef.cc)
target_link_libraries(chef ${catkin_LIBRARIES})

add_executable(pager src/pager.cc)
target_link_libraries(pager ${catkin_LIBRARIES})

add_executable(queue src/queue.cc)
target_link_libraries(queue ${catkin_LIBRARIES})
