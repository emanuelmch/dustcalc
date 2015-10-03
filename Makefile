SRC_DIR := ./src
TSS_DIR := ./tests
BUILD_DIR := ./build
DBG_DIR := $(BUILD_DIR)/debug
REL_DIR := $(BUILD_DIR)/release
PRF_DIR := $(BUILD_DIR)/profile
TST_DIR := $(BUILD_DIR)/test

FLAGS := -std=c++11 -Wall -Wextra -Wfloat-equal -Wundef -Wunreachable-code -Wswitch-enum -pedantic
FLAGS_DEBUG := -march=corei7-avx -mtune=corei7-avx -O0 -g
FLAGS_RELEASE := -march=corei7-avx -mtune=corei7-avx -O3 -Werror
FLAGS_PROFILE := $(FLAGS_RELEASE) -pg
LIBS :=
TEST_LIBS := -lcppunit

SRCS := $(shell find $(SRC_DIR) -type f -name \*.cpp)
DBG_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(DBG_DIR)/%.o, $(SRCS))
DBG_DEPS := $(patsubst $(SRC_DIR)/%.cpp, $(DBG_DIR)/%.d, $(SRCS))
REL_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(REL_DIR)/%.o, $(SRCS))
REL_DEPS := $(patsubst $(SRC_DIR)/%.cpp, $(REL_DIR)/%.d, $(SRCS))
PRF_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(PRF_DIR)/%.o, $(SRCS))
PRF_DEPS := $(patsubst $(SRC_DIR)/%.cpp, $(PRF_DIR)/%.d, $(SRCS))

TESTS := $(shell find $(TSS_DIR) -type f -name \*.cpp)
TST_OBJS := $(patsubst $(TSS_DIR)/%.cpp, $(TST_DIR)/%.o, $(TESTS))

all: release test

#
# RUNNER TARGETS
#
gdb: debug
	gdb ./debug

valgrind: debug
	valgrind --log-file=val.log --leak-check=full ./debug

valgrind_check: test
	valgrind --log-file=val.log --leak-check=full ./test

check: test
	./test

run: release
	./release

run_profile: profile
	./profile

#
# FINAL BINARY TARGETS
#
debug: $(DBG_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

release: $(REL_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

profile: $(PRF_OBJS)
	$(CXX) -o $@ $^ $(LIBS) -pg

test: $(TST_OBJS) $(subst $(REL_DIR)/main.o,,$(REL_OBJS))
	$(CXX) -o $@ $^ $(LIBS) $(TEST_LIBS)

#
# DEPENDENCIES TARGETS
#
$(DBG_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -std=c++11 -E -M -MM -MF $@ $<
# Gambiarras...
	@mv $@ $@.tmp
	@echo -n "$(DBG_DIR)/" > $@
	@cat $@.tmp >> $@
	@rm $@.tmp

$(REL_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -std=c++11 -E -M -MM -MF $@ $<
# Gambiarras...
	@mv $@ $@.tmp
	@echo -n "$(@D)/" > $@
	@cat $@.tmp >> $@
	@rm $@.tmp

$(PRF_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -std=c++11 -E -M -MM -MF $@ $<
# Gambiarras...
	@mv $@ $@.tmp
	@echo -n "$(@D)/" > $@
	@cat $@.tmp >> $@
	@rm $@.tmp

$(DBG_DIR)/%.o: $(DBG_DIR)/%.d
$(REL_DIR)/%.o: $(REL_DIR)/%.d
$(PRF_DIR)/%.o: $(PRF_DIR)/%.d

#
# OBJECT TARGETS
#
$(DBG_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $(INCLUDES) $(FLAGS_DEBUG) -c -o $@ $<

$(REL_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $(INCLUDES) $(FLAGS_RELEASE) -c -o $@ $<

$(PRF_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $(INCLUDES) $(FLAGS_PROFILE) -c -o $@ $<

$(TST_DIR)/%.o: $(TSS_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $(INCLUDES) $(FLAGS_RELEASE) -c -o $@ $<

#
# OTHER TARGETS
#
clean:
	rm -rf $(BUILD_DIR) release{,.exe} debug{,.exe} test{,.exe} profile{,.exe}

.PHONY: clean gdb valgrind valgrind_check check run run_profile

# Code dependencies are not necessary for these these targets
NODEPS := clean 

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DBG_DEPS)
-include $(REL_DEPS)
-include $(PRF_DEPS)
endif
