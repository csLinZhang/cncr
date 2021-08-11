define laser ranger
(
  sensor
  (
    range [0.1 20]
    fov 270.0
    samples 540
  )
  color "black"
  size [ 0.06 0.15 0.03 ]
)


define robot_raccoon_002 position
(  
  gui_nose 1
  color "red"
  localization "gps"

  drive "car"
  wheelbase 0.787
  
  # caution: origin's is offset from center(positive to tail, negtive to head),
  # lase pose's x is offset from laser to origin, while here front is positive
  size [ 1.563943 0.7 2.0 ]
  origin [0.372178 0 0 0]
  laser(pose [ 1.1541 0.0 -0.4 0.0 ]) # z is relative to the top of robot
)

define robot_zz01a position
(  
  gui_nose 1
  color "red"
  localization "gps"

  drive "car"
  wheelbase 0.682
  
  # caution: origin's is offset from center(positive to tail, negtive to head),
  # lase pose's x is offset from laser to origin, while here front is positive
  size [ 1.28 0.74 2.0 ]
  origin [0.212 0 0 0]
  laser(pose [ 1.068 0.0 -0.4 0.0 ]) # z is relative to the top of robot
)

define robot_tergeo position
(
  size [ 2.5 1.4 2.0 ]
  # center is (0,0), but direction to tail is positive.
  origin [ 0.65 0.0 0.0 0.0]
  gui_nose 1
  color "red"

  # kinematics
  drive "car"
  wheelbase 1.5 # distance between both axles
  
  # sensors
  laser(pose [ 1.9 0.0 -1.0 0.0 ]) # z is relative to the top of robot
)