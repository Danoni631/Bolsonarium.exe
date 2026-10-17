#pragma once

#include "Bolsonarium.h"

void EndPayload(HANDLE Payload)
{
	TerminateThread(Payload, 0);
	CloseHandle(Payload);
}