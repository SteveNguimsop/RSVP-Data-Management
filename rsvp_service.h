// file: rsvp_service.h
#ifndef RSVP_SERVICE_H
#define RSVP_SERVICE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

// Defines RSVP status options for players
enum class RsvpStatus { Yes, No, Maybe };

// Helper function to convert RSVP status to string
inline std::string statusToString(RsvpStatus status) {
    switch (status) {
        case RsvpStatus::Yes: return "Yes";
        case RsvpStatus::No: return "No";
        case RsvpStatus::Maybe: return "Maybe";
        default: return "Unknown";
    }
}

// Represents a player with a name
struct Player {
    std::string name;
};

// Represents a complete RSVP entry with player and their status
struct RsvpEntry {
    Player player;
    RsvpStatus status;
};

// Service class to manage all RSVP-related operations
class RsvpService {
private:
    // Stores mapping from player name to their RSVP status
    std::unordered_map<std::string, RsvpStatus> rsvpMap;

public:
    // Add a new RSVP or update existing one
    void addOrUpdateRsvp(const std::string& name, RsvpStatus status);

    // Add multiple RSVP entries at once
    void addMultipleRsvps(const std::vector<RsvpEntry>& entries);

    // Retrieve list of players who confirmed attendance (status == Yes)
    std::vector<std::string> getConfirmedAttendees() const;

    // Count how many players responded with Yes, No, or Maybe
    std::map<RsvpStatus, int> getStatusCounts() const;
};

#endif // RSVP_SERVICE_H
