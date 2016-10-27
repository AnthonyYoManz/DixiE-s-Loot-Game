#pragma once

class Input;
class StateManager;

struct GameInfo
{
	StateManager* m_stateManager;
	Input* m_input;
	float m_dt;
};