// file: main.cpp
#include "rsvp_service.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    RsvpService service;
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Failed to open input or output file." << std::endl;
        return 1;
    }

    // Read entries from input.txt, format: name,status
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::string name, statusStr;

        if (std::getline(iss, name, ',') && std::getline(iss, statusStr)) {
            RsvpStatus status;
            if (statusStr == "Yes") status = RsvpStatus::Yes;
            else if (statusStr == "No") status = RsvpStatus::No;
            else status = RsvpStatus::Maybe; // Default to Maybe if unknown

            service.addOrUpdateRsvp(name, status);
        }
    }

    // Write confirmed attendees to output file
    output << "Confirmed Attendees:\n";
    for (const auto& name : service.getConfirmedAttendees()) {
        output << name << "\n";
    }

    // Write RSVP status counts to output file
    output << "\nRSVP Counts:\n";
    auto counts = service.getStatusCounts();
    for (const auto& it : counts) {
        auto status = it.first;
        auto count = it.second;
        output << statusToString(status) << ": " << count << "\n";
    }

    // Write total number of responses to output file
    int totalResponses = 0;
    for (const auto& it : counts) {
        auto count = it.second; 
        totalResponses += count;
    }
    output << "\nTotal responses: " << totalResponses << "\n";

    return 0;
}