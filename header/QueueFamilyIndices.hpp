#ifndef QUEUE_FAMILY_INDICES
#define QUEUE_FAMILY_INDICES

#include <optional>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentationFamily;

	bool isComplete();
};

#endif