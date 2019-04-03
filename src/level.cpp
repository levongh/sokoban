#include <QFile>
#include <QTextStream>

#include "include/level.h"
#include "include/settings.h"

//Wall                  #   0x23
//Player                @   0x40
//Player on goal square +   0x2b
//Box                   $   0x24
//Box on goal square    *   0x2a
//Goal square           .   0x2e
//Floor            (Space)  0x20


Level::Level()
{

}

void Level::reset()
{}

Level::Field Level::getFieldFromChar(const char& ch, unsigned idx, unsigned column)
{
    switch (ch) {
    case '#':
        return Level::Field::WALL;
    case '@':
        m_playerPos.first  = idx;
        m_playerPos.second = column;
        return Level::Field::PLAYER;
    case '+':
        return Level::Field::PLAYER_ON_GOAL;
    case '$':
        return Level::Field::BOX;
    case '*':
        ++m_goalCount;
        ++m_boxOnGoal;
        return Level::Field::BOX_ON_GOAL;
    case '.':
        ++m_goalCount;
        return Level::Field::GOAL;
    case ' ':
        return Level::Field::EMPTY;
    default:
        return Level::Field::EMPTY;
    }
}

void Level::load(int level)
{
    const auto& levelPath = Settings::getInstance().levelsPath();
    QString lvl = levelPath + QString::number(level) + ".lvl";

    QFile file(lvl);
    m_isLoad= false;
    m_isComplete = false;
    m_goalCount = 0;
    m_boxOnGoal = 0;
    m_steps = 0;

    file.open(QIODevice::ReadOnly);
    if (file.isOpen()) {
        m_room.clear();
        QTextStream in(&file);
        in >> m_level;
        in >> m_column;
        in >> m_lines;

        std::vector<Field> tmpRoom(m_column * m_lines, Field::EMPTY);
        in.readLine();

        for(unsigned i = 0; i < m_lines; ++i) {
            QString line;
            line = in.readLine();

            unsigned  column = 0;
            unsigned  end    = line.size();

            while(column != end) {
                tmpRoom[m_column * i + column] = getFieldFromChar(line[column].toLatin1(), i, column);
                ++column;
            }
        }
    }
    file.close();
}

void Level::load(const std::string& levelFile)
{
    //TODO
    Q_UNUSED(levelFile)
}

bool Level::isCompleted()
{
    return m_isComplete;
}

bool Level::isLoad()
{
    return m_isLoad;
}

void Level::playerUp()
{

}

void Level::playerDown()
{

}

void Level::playerLeft()
{

}

void Level::playerright()
{

}

int Level::stepsCount() const
{
    return m_steps;
}

int Level::goals() const
{
    return m_goalCount;
}

int Level::boxesOnGoal() const
{
    return m_boxOnGoal;
}
