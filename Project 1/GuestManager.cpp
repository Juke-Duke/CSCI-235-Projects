#include "GuestManager.h"

/**
 * @param guestType GuestType enum class representing the type of guest.
 * @param roomType RoomType enum class representing the room service.
 * @param bookedDays Amount of days the guest will be holding the room for.
 */
Guest::Guest(GuestType guestType, RoomType roomType, int bookedDays) :
    guestType(guestType), roomType(roomType), bookedDays(bookedDays) {}

/**
 * @return GuestType enum class for this guest's type.
 */
GuestType Guest::GetGuestType() const { return guestType; }

/**
 * @return RoomType enum class for this guest's room service.
 */
RoomType Guest::GetRoomType() const { return roomType; }

/** 
 * @return Number of days the room is booked for.
 */
int Guest::GetBookedDays() const { return bookedDays; }

Guest::~Guest() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 
 * @param guestType GuestType enum class representing the type of guest.
 * @param roomType RoomType enum class representing the room service.
 * @param bookedDays Amount of days the guest will be holding the room for.
 */
Family::Family(GuestType guestType, RoomType roomType, int bookedDays) :
    Guest(guestType, roomType, bookedDays) {}

/** 
 * @return  Number of days the room will be occupied for.
 */
int Family::GetRoomBusyDays() const { return bookedDays; }

/**
 * @return Any additional income this guest is providing.
 */
int Family::GetAdditionalIncome() const { return 0; }

Family::~Family() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @param guestType GuestType enum class representing the type of guest.
 * @param roomType RoomType enum class representing the room service.
 * @param bookedDays Amount of days the guest will be holding the room for. 
 * @param additionalIncome Amount of additional income provided, default value is 0.
 */
Businessman::Businessman(GuestType guestType, RoomType roomType, int bookedDays, int additionalIncome)  :
    Guest(guestType, roomType, bookedDays), additionalIncome(additionalIncome) {}

/** 
 * @return  Number of days the room will be occupied for.
 */
int Businessman::GetRoomBusyDays() const { return bookedDays; }

/**
 * @return Any additional income this guest is providing.
 */
int Businessman::GetAdditionalIncome() const { return additionalIncome; }

Businessman::~Businessman() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 
 * @param guestType GuestType enum class representing the type of guest.
 * @param roomType RoomType enum class representing the room service.
 * @param bookedDays Amount of days the guest will be holding the room for.
 */
Rockstar::Rockstar(GuestType guestType, RoomType roomType, int bookedDays) :
    Guest(guestType, roomType, bookedDays) {}

/** 
 * @return  Number of days the room will be occupied for.
 */
int Rockstar::GetRoomBusyDays() const { return bookedDays + 10; }

/**
 * @return Any additional income this guest is providing.
 */
int Rockstar::GetAdditionalIncome() const { return 0; }

Rockstar::~Rockstar() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @param standardRooms Total amount of standard rooms.
 * @param dayPriceStandard Price per day for standard room service.
 * @param comfortRooms Total amount of comfort rooms.
 * @param dayPriceComfort Price per day for comfort room service.
 */
GuestManager::GuestManager(int standardRooms, int dayPriceStandard, int comfortRooms, int dayPriceComfort) :
    standardRooms(standardRooms), dayPriceStandard(dayPriceStandard), comfortRooms(comfortRooms), dayPriceComfort(dayPriceComfort), 
    MAX_STANDARD(standardRooms), MAX_COMFORT(comfortRooms) {}

/**
 * @brief This will take in arguments to construct a guest class to add into the vector of guest pointers if there is
 * available space for the desired room service. Will decrement the number of rooms left of that service if succesful.
 * O(1) Time Complexity.
 * 
 * @param guestType GuestType enum class representation for type of guest to be added.
 * @param roomType RoomType enum class representation for room service of guest to be added.
 * @param bookedDays Amount of days the guest will be holding the room for.
 * @param additionalIncome Amount of additional income provided, default value is 0.
 * 
 * @return True if the guest was succesfully added to the respected room, otherwise false.
 */
bool GuestManager::AddGuest(const GuestType guestType, const RoomType roomType, const int bookedDays, const int additionalIncome)
{
    if (!IsAvailable(roomType))
        return false;

    switch (guestType)
    {
    case GuestType::Family :
        guests.push_back(new Family(guestType, roomType, bookedDays));
        break;

    case GuestType::Businessman :
        guests.push_back(new Businessman(guestType, roomType, bookedDays, additionalIncome));
        break;

    case GuestType::Rockstar :
        guests.push_back(new Rockstar(guestType, roomType, bookedDays));
        break;
    }

    if (roomType == RoomType::Standard)
        --standardRooms;
    else if (roomType == RoomType::Comfort)
        --comfortRooms;

    return true;
}

/**
 * @brief Checks to see if there are available rooms or if a current guests busy days are less than or the same as the 
 * amount of days requested by looping throught the vector of pointers to guests and checking their busy days. 
 * O(N) Time Complexity, where N is amount of guest pointers in vector.
 * 
 * @param roomType RoomType enum class representation of room service to be checked for availability.
 * @param inDays Amount of days the room service is desired to be available in, default value is 0.
 * 
 * @return True if there is still available rooms or if a room will be available in the desired days, otherwise false.
 */
bool GuestManager::IsAvailable(const RoomType roomType, const int inDays) const
{
    if (roomType == RoomType::Standard && standardRooms > 0 
     || roomType == RoomType::Comfort && comfortRooms > 0)
        return true;

    for (Guest *guest : guests)
        if (guest->GetRoomType() == roomType && guest->GetRoomBusyDays() <= inDays)
            return true;

    return false;
}

/**
 * @brief Will loop through the vector of guests and compute all profit for all of their booked days.
 * O(N) Time Complexity, where N is amount of guest pointers in vector.
 * 
 * @return All profit and additional income all current guests will provide for their full stay.
 */
int GuestManager::IncomingProfit() const
{
    int profit = 0;

    for (Guest *guest : guests)
        if (guest->GetRoomType() == RoomType::Standard)
            profit += (dayPriceStandard + guest->GetAdditionalIncome()) * guest->GetBookedDays();
        else if (guest->GetRoomType() == RoomType::Comfort)
            profit += (dayPriceComfort + guest->GetAdditionalIncome()) * guest->GetBookedDays();

    return profit;
}

/**
 * @brief Will loop throughout the whole vector of guest pointers and compute the income each guest gives,
 * including additional income and sets a ratio to the maximum income with no additional cost for ALL rooms.
 * O(N) Time Complexity, where N is amount of guest pointers in vector.
 * 
 * @return Floating point value of current income with additional income for all 
 * booked rooms divided by maximum income with no additional cost for ALL rooms.
 */
float GuestManager::EarningEfficiency() const
{
    float maxPerDay = (MAX_STANDARD * dayPriceStandard) + (MAX_COMFORT * dayPriceComfort), 
          currPerDay = 0;

    if (maxPerDay == 0)
        return 0;

    for (Guest *guest : guests)
        if (guest->GetRoomType() == RoomType::Standard)
            currPerDay += dayPriceStandard + guest->GetAdditionalIncome();
        else if (guest->GetRoomType() == RoomType::Comfort)
            currPerDay += dayPriceComfort + guest->GetAdditionalIncome();

    return currPerDay / maxPerDay;
}

/**
 * @brief Overload for < operator, compares incoming profit of two GuestManagers.
 * O(1) Time Complexity.
 * 
 * @param otherGuestManager GuestManager to compare IncomingProift() to.
 * 
 * @return True if left GuestManager instance's IncomingProfit() is less than the right GuestManager instance's IncomingProfit().
 */
bool GuestManager::operator<(const GuestManager &otherGuestManager) const 
    { return IncomingProfit() < otherGuestManager.IncomingProfit(); }

/**
 * @brief Will loop through the vector of guest pointers and delete them to avoid leaking memory.
 * O(N) Time Complexity, where N is amount of guest pointers in vector.
 */
GuestManager::~GuestManager()
{
    for (Guest *guest : guests)
    {
        delete guest;
        guest = nullptr;
    }

    guests.clear();
}