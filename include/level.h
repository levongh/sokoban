#pragma once

//Wall 	                    # 	0x23
//Player 	                @ 	0x40
//Player on goal square 	+ 	0x2b
//Box 	                    $ 	0x24
//Box on goal square 	    * 	0x2a
//Goal square 	            . 	0x2e
//Floor 	        (Space) 	0x20

#include <string>
#include <vector>

class Level
{
    enum class Field
    {
        EMPTY,
        WALL,
        PLAYER,
        PLAYER_ON_GOAL,
        BOX,
        BOX_ON_GOAL,
        GOAL
    };

public:
    Level();
    void reset();
    void load(int level);
    void load(const std::string& levelFile);
    bool isCompleted();
    bool isLoad();

    void playerUp();
    void playerDown();
    void playerLeft();
    void playerright();

    int stepsCount() const;
    int goals() const;
    int boxesOnGoal() const;

private:
    Field getFieldFromChar(const char& ch, unsigned idx, unsigned column);

private:
    int m_level{-1};
    unsigned m_column{0};
    unsigned m_lines{0};
    int m_steps{0};
    int m_goalCount{0};
    int m_boxOnGoal{0};

    bool m_isComplete{false};
    bool m_isLoad{false};

    std::pair<unsigned, unsigned> m_playerPos;
    std::vector<Field> m_room;
};
