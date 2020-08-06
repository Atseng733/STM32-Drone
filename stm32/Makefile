FILENAME = stm32
PROGRAMMER = usbasp
COMPILE = arm-none-eabi-g++ -mthumb -mcpu=cortex-m4 --std=c++14 -O2 -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections
LINK = arm-none-eabi-g++ -mthumb -mcpu=cortex-m4 -T linkerscript.ld -nostartfiles
INC_FLAGS := -I include -I lib/header
SRCS := $(wildcard src/*.cpp) $(wildcard lib/src/*.cpp)
OBJS := $(patsubst src/%.cpp,build/%.o,$(SRCS))
BUILD_DIR = build
vpath %.cpp src
vpath %.cpp lib
vpath %.bin build
vpath %.elf build

all: compile flash

flash: $(FILENAME).bin
	st-flash write $< 0x8000000
	arm-none-eabi-size $(BUILD_DIR)/$(FILENAME).elf

compile: $(FILENAME).bin

$(BUILD_DIR)/$(FILENAME).bin: $(FILENAME).elf
	arm-none-eabi-objcopy -O binary $< $@

$(BUILD_DIR)/$(FILENAME).elf: $(OBJS)
	#arm-none-eabi-g++ -Wall -Os -mcpu=cortex-m4 -o $@ $(OBJS)
	$(LINK) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.cpp $(BUILD_DIR)
	$(COMPILE) $(INC_FLAGS) $(COMPILE_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

erase:
	st-flash erase

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)