#pragma once

#include "traffic.h"
#include <iostream>

class Bridge
{
public:
	Bridge(int oneSideMaxCarCount) : m_left( this, true, oneSideMaxCarCount ), m_right (this, false, oneSideMaxCarCount)
	{}

	void pushLeftSide(std::thread::id id)
	{
		m_left.push(id);
	}

	void pushRightSide(std::thread::id id)
	{
		m_right.push(id);
	}

	void popLeftSide()
	{
		m_left.pop();
	}

	void popRightSide()
	{
		m_right.pop();
	}

	// unlock locked direction and vice versa 
	void switchDirection()
	{	
		if (m_left.getExecState())
		{
			// if right side is empty there is no any reason to switch 
			if (!m_right.empty())
			{
				// it is safe to have two locked direction same time
				// stop execution first
				m_left.setExecState(false);
			}
		}
		else
		{
			// if left side is empty there is no any reason to switch 
			if (!m_left.empty())
			{
				// it is safe to have two locked direction same time
				// stop execution first
				m_right.setExecState(false);				
			}
		}
	}

	void notify(Traffic* ptr, Traffic::Status st) 
	{
		if (st == Traffic::Status::Empty)
		{
			if (ptr == &m_left)
			{
				m_right.setExecState(true);
			}
			else if (ptr  == &m_right){
				m_left.setExecState(true);
			}
		}
	}

private:
	// left side traffic 
	Traffic m_left;
	// right side traffic
	Traffic m_right;

	// Note: only one traffic can be running at time
};

