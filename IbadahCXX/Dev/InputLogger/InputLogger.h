#include <cstdint>

#include <godot_cpp/classes/node.hpp>

#define INPUT_FORWARD (1u)
#define INPUT_BACKWARD (1u << 1)
#define INPUT_RIGHT (1u << 3)
#define INPUT_LEFT (1u << 2)
#define INPUT_PUSHTOTALK (1u << 3)

typedef struct{
	uint8_t continuous_inputs;
	uint8_t interrupt_inputs;
}InputLog;


class InputLogger{
	public:
		void read_cont_inputs(void);
		void read_interupt_inputs(void);
		void zero_input_log(void);
		const InputLog& get_input_log() const;
	private:
		InputLog input_logs_;
};
