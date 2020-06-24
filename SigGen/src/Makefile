FILENAME = SignalGenerator
DEVICE = atmega328
PROGRAMMER = usbasp
COMPILE = avr-gcc -Wall -Os -mmcu=$(DEVICE)
INC_FLAGS := -I ../include
CXXFLAGS := $(INC_FLAGS) -MMD -MP
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(OBJS:.o=.d)

upload: $(FILENAME).elf
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -U flash:w:$(FILENAME).hex:i

$(FILENAME).elf: $(OBJS)
	$(COMPILE) -o SignalGenerator.elf avr_io.o main.o 
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf


# c++ source
%.o: %.cpp
	$(COMPILE) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	rm $(OBJS)
	rm $(DEPS)

-include $(DEPS)