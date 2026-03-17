#include <cstdint>

#include <godot_cpp/classes/node.hpp>

#define INPUT_FORWARD (1u)
#define INPUT_BACKWARD (1u << 1)
#define INPUT_RIGHT (1u << 3)
#define INPUT_LEFT (1u << 2)
#define INPUT_PUSHTOTALK (1u << 3)

typedef struct{
	uint8_t continuousInputs;
	uint8_t interruptInputs;
}InputLogs;


class InputLogger{
	public:
		void readContinuousInputs(void);
		void readInterruptInputs(void);
		void zeroOutInputLog(void);
		InputLogs getInputLogs() const;
	private:
		InputLogs m_inputLogs;
};
