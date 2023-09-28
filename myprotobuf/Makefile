


all:
	./protobuf-3.19.4/src/protoc student.proto --cpp_out=./
	g++ -std=c++14 -I./protobuf-3.19.4/src/ -L./protobuf-3.19.4/src/.libs -lprotobuf  test.cpp student.pb.cc
#	g++ -std=c++11 -I./protobuf-3.19.4/src/ -L./protobuf-3.19.4/src/.libs -lprotobuf est.cpp student.pb.cc `pkg-config --cflags --libs protobuf`
#	g++ -I/home/lixiang/code/protobuf/src -I/home/lixiang/.cache/bazel/_bazel_lixiang/7019b445a0b1ff55bfbc59e169b8ae99/external/com_google_absl -static -L./ -lprotobuf  test.cpp student.pb.cc



