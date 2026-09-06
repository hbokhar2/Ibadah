#pragma once

#include <cstdint>
#include <array>

#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/input.hpp>

namespace Input {

#define MAX_LOG_SIZE 32

#define INPUT_FORWARD (1u)
#define INPUT_BACKWARD (1u << 1)
#define INPUT_RIGHT (1u << 2)
#define INPUT_LEFT (1u << 3)
#define INPUT_JUMP (1u << 4)
#define INPUT_CROUCH (1u << 5)
#define INPUT_INTERACT (1u << 6)
#define INPUT_PLACE (1u << 7)
#define INPUT_RECORD_MIC (1u << 8)

typedef struct 
{
	uint16_t buttons;
	godot::Vector2 cameraDelta;
}
InputFrame;

using InputLog = std::array<InputFrame, MAX_LOG_SIZE>;

class InputProcessor
{
	public:
		InputProcessor(uint8_t playerId);

		void processInputPoll();
		void processInputEvent(const godot::Ref<godot::InputEvent>& p_event);

		void commitInputFrame();
		InputFrame& getUnprocessedFrame();

	private:
		uint8_t m_playerId;

		godot::Vector2 m_mouseDelta;
		InputFrame m_inputFrame;
		InputLog m_inputLog;

		uint8_t m_producerIndex;
		uint8_t m_consumerIndex;
};

}
