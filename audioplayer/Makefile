FILENAME = stm32
PROGRAMMER = usbasp
PROCESSOR = cortex-m3
DEVICE = stm32f103
COMPILE = arm-none-eabi-g++ -mthumb -mcpu=$(PROCESSOR) --std=c++11 -O2 -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections
LINK = arm-none-eabi-g++ -mthumb -mcpu=$(PROCESSOR) -T linker/$(DEVICE).ld -nostartfiles
INC_FLAGS := -I lib/header
SRCS := $(wildcard lib/src/*.cpp)
OBJS := $(patsubst lib/src/%.cpp,build/%.o,$(SRCS))
BUILD_DIR = build
vpath %.cpp lib/src
#vpath %.cpp lib
vpath %.bin build
vpath %.elf build

f103: DEVICE = stm32f103
f103: PROCESSOR = cortex-m3
f103: compile flash

f407: DEVICE = stm32f407
f407: PROCESSOR = cortex-m4
f407: compile flash

flash: $(FILENAME).bin
	st-flash write $< 0x8000000
	arm-none-eabi-size $(BUILD_DIR)/$(FILENAME).elf

debug: COMPILE = arm-none-eabi-g++ -g -mthumb -mcpu=$(PROCESSOR) --std=c++14 -Og -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections
debug: $(FILENAME).bin

compile: COMPILE = arm-none-eabi-g++ -mthumb -mcpu=$(PROCESSOR) --std=c++14 -O2 -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections
compile: $(FILENAME).bin

$(BUILD_DIR)/$(FILENAME).bin: $(FILENAME).elf
	arm-none-eabi-objcopy -O binary $< $@

$(BUILD_DIR)/$(FILENAME).elf: $(OBJS)
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