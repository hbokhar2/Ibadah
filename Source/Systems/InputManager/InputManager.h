#pragma once

#include <cstdint>
#include <array>

#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/input.hpp>

#define MAX_LOG_SIZE 32

#define INPUT_FORWARD (1u)
#define INPUT_BACKWARD (1u << 1)
#define INPUT_RIGHT (1u << 2)
#define INPUT_LEFT (1u << 3)
#define INPUT_JUMP (1u << 4)
#define INPUT_SPRINT (1u << 5)

#define INPUT_CROUCH (1u << 6)
#define INPUT_INTERACT (1u << 7)
#define INPUT_PLACE (1u << 8)
#define INPUT_RECORD_MIC (1u << 9)

typedef struct {
	uint16_t buttons;
	godot::Vector2 cameraDelta;
}
InputFrame;

class InputManager{
public:
	InputManager();

	void processInputPoll();
	void processInputEvent(const godot::Ref<godot::InputEvent>& p_event);

	void commitInputFrame();
	InputFrame& getUnprocessedInputFrame();

private:
	godot::Vector2 mouseDelta_;

	InputFrame inputFrame_;
	std::array<InputFrame, MAX_LOG_SIZE> inputLog_;

	uint8_t producerIndex_;
	uint8_t consumerIndex_;
};
