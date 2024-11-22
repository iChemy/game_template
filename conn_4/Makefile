BUILD_DIR = ../build/conn_4
OUT_DIR = ../out/conn_4

TARGETS = $(OUT_DIR)/main $(OUT_DIR)/test

CXX = g++
CXXFLAGS = -std=c++17 -I/Library/Developer/CommandLineTools/SDKs/MacOSX15.0.sdk/usr/include/c++/v1 -Wall -Wextra -g
LDFLAGS =

# 各ターゲットごとのソースファイルを指定
MAIN_SRCS = main.cpp def.cpp evaluator.cpp bitfield_operation.cpp stream.cpp play.cpp game_tree.cpp
MAIN_OBJS = $(addprefix $(BUILD_DIR)/, $(MAIN_SRCS:.cpp=.o))

TEST_SRCS = test.cpp def.cpp evaluator.cpp bitfield_operation.cpp stream.cpp play.cpp game_tree.cpp
TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.cpp=.o))

all: $(TARGETS)

# main 実行ファイル
$(OUT_DIR)/main: $(MAIN_OBJS)
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# test 実行ファイル
$(OUT_DIR)/test: $(TEST_OBJS)
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 各オブジェクトファイルの生成ルール
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)
