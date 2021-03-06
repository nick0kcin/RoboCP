cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(RoboCP)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)

#find_package(PCL 1.2 REQUIRED)

#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

#FIND_PACKAGE(Boost REQUIRED COMPONENTS serialization)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#ADD_DEFINITIONS( "-DHAS_BOOST" )

find_package( OpenCV REQUIRED )


project(Robot)

add_executable (Robot
	RoboCPCommon/Controller.h RoboCPCommon/Controller.cpp
	RoboCPCommon/SenderBase.h RoboCPCommon/SenderBase.cpp
	RoboCPCommon/ReceivedBuffer.h RoboCPCommon/ReceivedBuffer.cpp
	RoboCPCommon/Command.h RoboCPCommon/Command.cpp

	RoboCPCommon/Send.h RoboCPCommon/Send.cpp
	RoboCPCommon/SendBuffer.h 
	
	RoboCPCommon/KinectData.h RoboCPCommon/KinectData.cpp
	RoboCPCommon/KinectBuffer.h 
	
	RoboCPCommon/XMLConfig.h RoboCPCommon/XMLConfig.cpp

	RoboCPCommon/Point3d.h

	
	RoboCPRobot/CommandProcessing.h RoboCPRobot/CommandProcessing.cpp
	RoboCPRobot/CommandBuffer.h RoboCPRobot/Configs/CommandConfig.h
	RoboCPRobot/Configs/CommandConfig.cpp

	RoboCPRobot/Received.h RoboCPRobot/Received.cpp 
	RoboCPRobot/IReceived.h RoboCPRobot/IReceived.cpp
	RoboCPRobot/ClientReceiver.h RoboCPRobot/ClientReceiver.cpp
	
	RoboCPRobot/ArduCopterController.h RoboCPRobot/ArduCopterController.cpp
	RoboCPRobot/ArduCopterReceived.h RoboCPRobot/ArduCopterReceived.cpp
	RoboCPRobot/ArduCopterBuffer.h RoboCPRobot/Configs/ArducopterConfig.h
	RoboCPRobot/Configs/ArducopterConfig.cpp
	
	RoboCPRobot/NanoController.h RoboCPRobot/NanoController.cpp
	RoboCPRobot/NanoReceived.h RoboCPRobot/NanoReceived.cpp
	RoboCPRobot/NanoReceivedBuffer.h RoboCPRobot/Configs/CarduinoConfig.h
	RoboCPRobot/Configs/CarduinoConfig.cpp

	RoboCPRobot/CameraController.h RoboCPRobot/CameraController.cpp
	RoboCPRobot/CameraReceived.h RoboCPRobot/CameraReceived.cpp
	RoboCPRobot/CameraReceivedBuffer.h RoboCPRobot/Configs/CameraConfig.h
	RoboCPRobot/Configs/CameraConfig.cpp
	
	RoboCPRobot/DisplacementImages.h RoboCPRobot/DisplacementImages.cpp
	RoboCPRobot/ImageFlowProcessing.h RoboCPRobot/ImageFlowProcessing.cpp

	RoboCPRobot/SendSender.h RoboCPRobot/SendSender.cpp
	RoboCPRobot/SendProcessing.h RoboCPRobot/SendProcessing.cpp
	RoboCPRobot/Configs/SendConfig.h RoboCPRobot/Configs/SendConfig.cpp

	RoboCPRobot/KinectController.h RoboCPRobot/KinectController.cpp
	RoboCPRobot/KinectSender.h RoboCPRobot/KinectSender.cpp
	RoboCPRobot/KinectDownsampler.h RoboCPRobot/KinectDownsampler.cpp
	RoboCPRobot/Configs/KinectConfig.h RoboCPRobot/Configs/KinectConfig.cpp

	RoboCPRobot/SerialCom.h RoboCPRobot/SerialCom.cpp 
	
	RoboCPRobot/Configs/configFactory.h RoboCPRobot/Configs/OctreeEncoderConfig.h
	RoboCPRobot/Configs/configFactory.cpp RoboCPRobot/Configs/OctreeEncoderConfig.cpp
	RoboCPRobot/Config.h RoboCPRobot/Config.cpp
	
	RoboCPRobot/main.cpp

)
target_include_directories(Robot PRIVATE RoboCPCommon RoboCPRobot RoboCPRobot/Configs)
target_compile_definitions(Robot PRIVATE _CRT_SECURE_NO_WARNINGS)
#target_link_libraries (Robot Qt5::Network Qt5::Xml ${PCL_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries (Robot Qt5::Network Qt5::Xml  ${OpenCV_LIBS})


project(Server)

add_executable (Server
	RoboCPCommon/Controller.h RoboCPCommon/Controller.cpp
	RoboCPCommon/SenderBase.h RoboCPCommon/SenderBase.cpp
	RoboCPCommon/ReceivedBuffer.h RoboCPCommon/ReceivedBuffer.cpp
	RoboCPCommon/Command.h RoboCPCommon/Command.cpp

	RoboCPCommon/Send.h RoboCPCommon/Send.cpp
	RoboCPCommon/SendBuffer.h 
	
	RoboCPCommon/KinectData.h RoboCPCommon/KinectData.cpp
	RoboCPCommon/KinectBuffer.h 

	RoboCPCommon/XMLConfig.h RoboCPCommon/XMLConfig.cpp

	RoboCPCommon/Point3d.h


	RoboCPRobot/DisplacementImages.h


	RoboCPServer/KinectViewer.h RoboCPServer/KinectViewer.cpp
	RoboCPServer/KinectReceiver.h RoboCPServer/KinectReceiver.cpp
	RoboCPServer/KinectManager.h RoboCPServer/KinectManager.cpp
	RoboCPServer/SendReceiver.h RoboCPServer/SendReceiver.cpp
	RoboCPServer/SendManager.h RoboCPServer/SendManager.cpp
	RoboCPServer/CommandMaker.h RoboCPServer/CommandMaker.cpp

	RoboCPServer/main.cpp

)
target_include_directories(Server PRIVATE RoboCPCommon RoboCPServer RoboCPRobot)
target_compile_definitions(Server PRIVATE _CRT_SECURE_NO_WARNINGS)
#target_link_libraries (Server Qt5::Network Qt5::Xml ${PCL_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries (Server Qt5::Network Qt5::Xml ${OpenCV_LIBS})
