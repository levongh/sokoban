#pragma once

class Settings
{
public:
    Settings(const Settings& other) = delete;
    Settings& operator= (const Settings& other) = delete;

public:
    void load();
    void save();

    unsigned screenWidth() const;
    unsigned screenHeight() const;

public:
    static Settings& getInstance();

private:
    Settings();
    ~Settings();

private:
    unsigned m_scrrenWidth{0};
    unsigned m_scrrenHeight{0};
};

