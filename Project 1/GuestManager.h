#pragma once
#include <vector>

enum class RoomType
{
    Standard,
    Comfort
};

enum class GuestType
{
    Family,
    Businessman,
    Rockstar
};

class Guest
{
protected:
    GuestType guestType;
    RoomType roomType;
    int bookedDays;

public:
    Guest(GuestType guestType, RoomType roomType, int bookedDays);

    GuestType GetGuestType() const;
    RoomType GetRoomType() const;
    int GetBookedDays() const;
    virtual int GetRoomBusyDays() const = 0;
    virtual int GetAdditionalIncome() const = 0;

    virtual ~Guest();
};

class Family : public Guest
{
public:
    Family(GuestType guestType, RoomType roomType, int bookedDays);

    int GetRoomBusyDays() const override;
    int GetAdditionalIncome() const override;

    ~Family();
};

class Businessman : public Guest
{
private:
    int additionalIncome;

public:
    Businessman(GuestType guestType, RoomType roomType, int bookedDays, const int additionalIncome = 0);

    int GetRoomBusyDays() const override;
    int GetAdditionalIncome() const override;

    ~Businessman();
};

class Rockstar : public Guest
{
public:
    Rockstar(GuestType guestType, RoomType roomType, int bookedDays);

    int GetRoomBusyDays() const override;
    int GetAdditionalIncome() const override;

    ~Rockstar();
};

class GuestManager
{
private:
    std::vector<Guest *> guests;
    const int MAX_STANDARD, MAX_COMFORT, dayPriceStandard, dayPriceComfort;
    int standardRooms, comfortRooms;

public:
    GuestManager(int standardRooms, int dayPriceStandard, int comfortRooms, int dayPriceComfort);

    bool AddGuest(const GuestType guestType, const RoomType roomType, const int bookedDays, const int additionalIncome = 0);
    bool IsAvailable(const RoomType roomType, const int inDays = 0) const;
    int IncomingProfit() const;
    float EarningEfficiency() const;
    bool operator<(const GuestManager &otherGuestManager) const;

    ~GuestManager();
};