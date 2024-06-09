#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ctime>
using namespace std;

class Movie {
public:
    string title;
    string synopsis;
    string duration;
    string genre;
    vector<string> schedules;
    double price;

    Movie(string title, string synopsis, string duration, string genre, vector<string> schedules, double price)
        : title(title), synopsis(synopsis), duration(duration), genre(genre), schedules(schedules), price(price) {}

    // Getter and Setter
    string getTitle() const { return title; }
    string getSynopsis() const { return synopsis; }
    string getDuration() const { return duration; }
    string getGenre() const { return genre; }
    vector<string> getSchedules() const { return schedules; }
    double getPrice() const { return price; }

    void setTitle(const string& newTitle) { title = newTitle; }
    void setSynopsis(const string& newSynopsis) { synopsis = newSynopsis; }
    void setDuration(const string& newDuration) { duration = newDuration; }
    void setGenre(const string& newGenre) { genre = newGenre; }
    void setSchedules(const vector<string>& newSchedules) { schedules = newSchedules; }
    void setPrice(double newPrice) { price = newPrice; }

    // Polymorphism - Overriding
    virtual void displayDetails() const {
        cout << "Title: " << title << "\n";
        cout << "Synopsis: " << synopsis << "\n";
        cout << "Duration: " << duration << "\n";
        cout << "Genre: " << genre << "\n";
        cout << "Price: $" << price << "\n";
    }
};

class Theater {
public:
    string name;
    vector<Movie> movies;

    Theater(string name, vector<Movie> movies)
        : name(name), movies(movies) {}

    // Abstraction - Polymorphism
    void displayMovies() const {
        cout << "Movies available in " << name << ":\n";
        for (const Movie& movie : movies) {
            movie.displayDetails();
            cout << endl;
        }
    }
};

class Booking {
public:
    int bookingID;
    string movieTitle;
    string schedule;
    string theater;
    vector<int> seatNumbers;
    int ticketQuantity;
    string purchaseTime;
    string paymentMethod;

    Booking(int bookingID, string movieTitle, string schedule, string theater, vector<int> seatNumbers, int ticketQuantity, string purchaseTime, string paymentMethod)
        : bookingID(bookingID), movieTitle(movieTitle), schedule(schedule), theater(theater), seatNumbers(seatNumbers), ticketQuantity(ticketQuantity), purchaseTime(purchaseTime), paymentMethod(paymentMethod) {}
};

class User {
public:
    string username;
    string password;
    vector<Booking> userBookings;

    User(string username, string password) : username(username), password(password) {}

    // Encapsulation - Setter and Getter
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    vector<Booking> getUserBookings() const { return userBookings; }

    void setUsername(const string& newUsername) { username = newUsername; }
    void setPassword(const string& newPassword) { password = newPassword; }
    void setUserBookings(const vector<Booking>& newBookings) { userBookings = newBookings; }
};

class CinemaSystem {
private:
    vector<Theater> theaters;
    vector<Movie> playingNow;
    vector<Movie> comingSoon;
    vector<User> users;
    unordered_map<string, unordered_map<string, unordered_set<int>>> bookedSeats;
    vector<Booking> bookings;
    int nextBookingID;
    User* loggedInUser;

public:
    CinemaSystem(vector<Theater> theaters, vector<Movie> playingNow, vector<Movie> comingSoon, vector<User> users)
        : theaters(theaters), playingNow(playingNow), comingSoon(comingSoon), users(users), nextBookingID(1), loggedInUser(nullptr) {}

    void registerUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        users.push_back(User(username, password));
        cout << "Registration successful!\n";
    }

    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (User& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                loggedInUser = &user;
                cout << "Login successful!\n";
                return;
            }
        }

        cout << "Invalid username or password.\n";
    }

    void logout() {
        loggedInUser = nullptr;
        cout << "Logout successful!\n";
    }

    void displayNowPlayingMovies() const {
        cout << "Now Playing:\n";
        for (size_t i = 0; i < playingNow.size(); ++i) {
            cout << "\n" ;
            cout << i + 1 << ". " << playingNow[i].getTitle() << " (" << playingNow[i].getGenre() << ", " << playingNow[i].getDuration() << ")\nSynopsis:\n " << playingNow[i].getSynopsis() << "\n";
        }
    }

    void displayComingSoonMovies() const {
        cout << "Coming Soon:\n";
        for (size_t i = 0; i < comingSoon.size(); ++i) {
            cout << "\n" ;
            cout << i + 1 << ". " << comingSoon[i].getTitle() << " (" << comingSoon[i].getGenre() << ", " << comingSoon[i].getDuration() << ")\nSynopsis:\n " << comingSoon[i].getSynopsis() << "\n";
        }
    }

    void displayMovies(const vector<Movie>& movies) const {
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << "\n";
            cout << i + 1 << ". " << movies[i].getTitle() << " (" << movies[i].getGenre() << ", " << movies[i].getDuration() << ")\nSynopsis: " << movies[i].getSynopsis() << "\n";
        }
    }

    void displayMovieDetails(const Movie& movie) const {
        movie.displayDetails();
    }

    void displaySchedules(const Movie& movie) const {
        cout << "Available schedules:\n";
        for (size_t i = 0; i < movie.getSchedules().size(); ++i) {
            cout << i + 1 << ". " << movie.getSchedules()[i] << "\n";
        }
    }

    void displayTheaters(const vector<Theater>& theaters) const {
        for (size_t i = 0; i < theaters.size(); ++i) {
            cout << i + 1 << ". " << theaters[i].name << "\n";
        }
    }

    void displaySeats(const unordered_set<int>& bookedSeats, int totalSeats) const {
        cout << "Available seats (1-" << totalSeats << "):\n";
        for (int i = 1; i <= totalSeats; ++i) {
            if (bookedSeats.count(i) == 0) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }

    void displayBookingHistory() const {
        if (loggedInUser->getUserBookings().empty()) {
            cout << "No booking history.\n";
            return;
        }

        for (const Booking& booking : loggedInUser->getUserBookings()) {
            cout << "\nBooking ID: " << booking.bookingID << "\n";
            cout << "Movie: " << booking.movieTitle << "\n";
            cout << "Schedule: " << booking.schedule << "\n";
            cout << "Theater: " << booking.theater << "\n";
            cout << "Seats: ";
            for (int seat : booking.seatNumbers) {
                cout << seat << " ";
            }
            cout << "\n\n";
            cout << "Quantity: " << booking.ticketQuantity << "\n";
            cout << "Purchase Time: " << booking.purchaseTime << "\n";
            cout << "Payment Method: " << booking.paymentMethod << "\n\n";
        }
    }

    void viewTicket() const {
        int bookingID;
        cout << "Enter booking ID to view: ";
        cin >> bookingID;

        for (const Booking& booking : bookings) {
            if (booking.bookingID == bookingID) {
                printTicket(booking);
                return;
            }
        }

        cout << "Booking ID not found.\n";
    }

    double calculateTotalPrice(const Movie& movie, int ticketQuantity) const {
        return movie.getPrice() * ticketQuantity;
    }

    string getCurrentTime() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
        return string(buffer);
    }

    vector<int> getAvailableTheatersForMovieSchedule(const string& movieTitle, const string& schedule) const {
        vector<int> availableTheaterIndices;
        for (size_t i = 0; i < theaters.size(); ++i) {
            for (const Movie& movie : theaters[i].movies) {
                if (movie.getTitle() == movieTitle && find(movie.getSchedules().begin(), movie.getSchedules().end(), schedule) != movie.getSchedules().end()) {
                    availableTheaterIndices.push_back(i);
                    break;
                }
            }
        }
        return availableTheaterIndices;
    }

    void printTicket(const Booking& booking) const {
        cout << "-----------------------------------\n";
        cout << "              TICKET\n";
        cout << "------------------------------------\n";
        cout << "Booking ID: " << booking.bookingID << "\n";
        cout << "Movie: " << booking.movieTitle << "\n";
        cout << "Schedule: " << booking.schedule << "\n";
        cout << "Theater: " << booking.theater << "\n";
        cout << "Seats: ";
        for (int seat : booking.seatNumbers) {
            cout << seat << " ";
        }
        cout << "\n\n";
        cout << "Quantity: " << booking.ticketQuantity << "\n";
        cout << "Purchase Time: " << booking.purchaseTime << "\n";
        cout << "Payment Method: " << booking.paymentMethod << "\n\n";
    }

 void bookTicket() {
    if (loggedInUser == nullptr) {
        cout << "You need to log in to book a ticket.\n";
        return;
    }

    displayMovies(playingNow);

    int movieChoice;
    cout << "Enter the number of the movie you want to book: ";
    cin >> movieChoice;

    if (movieChoice < 1 || movieChoice > playingNow.size()) {
        cout << "Invalid movie choice.\n";
        return;
    }

    Movie& selectedMovie = playingNow[movieChoice - 1];
    displaySchedules(selectedMovie);

    int scheduleChoice;
    cout << "Enter the number of the schedule you want to book: ";
    cin >> scheduleChoice;

    if (scheduleChoice < 1 || scheduleChoice > selectedMovie.getSchedules().size()) {
        cout << "Invalid schedule choice.\n";
        return;
    }

    string selectedSchedule = selectedMovie.getSchedules()[scheduleChoice - 1];
    vector<int> availableTheaters = getAvailableTheatersForMovieSchedule(selectedMovie.getTitle(), selectedSchedule);

    if (availableTheaters.empty()) {
        cout << "No theaters available for the selected movie and schedule.\n";
        return;
    }

    displayTheaters(theaters);

    int theaterChoice;
    cout << "Enter the number of the theater you want to book: ";
    cin >> theaterChoice;

    if (theaterChoice < 1 || theaterChoice > theaters.size()) {
        cout << "Invalid theater choice.\n";
        return;
    }

    Theater& selectedTheater = theaters[theaterChoice - 1];
    unordered_set<int>& theaterBookedSeats = bookedSeats[selectedTheater.name][selectedSchedule];

    int totalSeats = 80; 
    displaySeats(theaterBookedSeats, totalSeats);

    int ticketQuantity;
    cout << "Enter the number of tickets you want to book: ";
    cin >> ticketQuantity;

    if (ticketQuantity < 1 || ticketQuantity > totalSeats - theaterBookedSeats.size()) {
        cout << "Invalid ticket quantity.\n";
        return;
    }

    vector<int> seatNumbers;
    for (int i = 0; i < ticketQuantity; ++i) {
        int seatNumber;
        cout << "Enter seat number " << i + 1 << ": ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > totalSeats || theaterBookedSeats.count(seatNumber) > 0) {
            cout << "Invalid or already booked seat number.\n";
            return;
        }

        seatNumbers.push_back(seatNumber);
    }

    double totalPrice = calculateTotalPrice(selectedMovie, ticketQuantity);
    cout << "Total price: $" << totalPrice << "\n";

    string paymentMethod;
    cout << "Enter payment method (e.g., Credit Card, PayPal): ";
    cin >> paymentMethod;

    string purchaseTime = getCurrentTime();
    Booking newBooking(nextBookingID++, selectedMovie.getTitle(), selectedSchedule, selectedTheater.name, seatNumbers, ticketQuantity, purchaseTime, paymentMethod);

    loggedInUser->userBookings.push_back(newBooking);
    bookings.push_back(newBooking);

    for (int seat : seatNumbers) {
        theaterBookedSeats.insert(seat);
    }

    cout << "Booking successful!\n";
    printTicket(newBooking);
}



    void run() {
        int choice;
        do {
            if (loggedInUser == nullptr) {
                cout << "\n-------------------------\n";
                cout << "Welcome to Cinema System\n";
                cout << "-------------------------\n";
                cout << "1. Register\n";
                cout << "2. Login\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        registerUser();
                        break;
                    case 2:
                        login();
                        break;
                    case 3:
                        cout << "Thank you for using Cinema System. Goodbye!\n";
                        break;
                    default:
                        cout << "Invalid choice. Please enter a number between 1 and 3.\n";
                }
            } else {
                cout << "\n---------------------------\n";
                cout << "    Cinema Booking System    \n" << loggedInUser->getUsername() << "!\n";
                cout << "---------------------------\n";
                cout << "1. Now Playing\n";
                cout << "2. UpComing Movies\n";
                cout << "3. Book Ticket\n";
                cout << "4. View Booking History\n";
                cout << "5. View Ticket\n";
                cout << "6. Logout\n";
                cout << "7. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        displayNowPlayingMovies();
                        break;
                    case 2:
                        displayComingSoonMovies();
                        break;
                    case 3:
                        bookTicket();
                        break;
                    case 4:
                        displayBookingHistory();
                        break;
                    case 5:
                        viewTicket();
                        break;
                    case 6:
                        logout();
                        break;
                    case 7:
                        cout << "Thank you for using Cinema System. Goodbye!\n";
                        break;
                    default:
                        cout << "Invalid choice. Please enter a number between 1 and 7.\n";
                }
            }
        } while (choice != 7);
    }
};

int main() {
    vector<Movie> playingNow = {
        Movie("The Batman", "Two years of nights have turned Bruce Wayne into a nocturnal animal. But as he continues to find his way as Gotham's dark knight Bruce is forced into a game of cat and mouse with his biggest threat so far, a manic killer known as 'The Riddler' who is filled with rage and determined to expose the corrupt system whilst picking off all of Gotham's key political figures. Working with both established and new allies, Bruce must track down the killer and see him brought to justice, while investigating his father's true legacy and questioning the effect that he has had on Gotham so far as 'The Batman.'", "2h 55m", "Action", {"10:00", "13:00", "16:00", "19:00"}, 10.0),
        Movie("Spider-Man: No Way Home", "Peter Parker's secret identity is revealed to the entire world. Desperate for help, Peter turns to Doctor Strange to make the world forget that he is Spider-Man. The spell goes horribly wrong and shatters the multiverse, bringing in monstrous villains that could destroy the world.", "2h 30m", "Action", {"11:00", "14:00", "17:00", "20:00"}, 12.0),
        Movie("Doctor Strange in the Multiverse of Madness", "Marvel's 'Doctor Strange' follows the story of the talented neurosurgeon Doctor Stephen Strange who, after a tragic car accident, must put ego aside and learn the secrets of a hidden world of mysticism and alternate dimensions. Based in New York City's Greenwich Village, Doctor Strange must act as an intermediary between the real world and what lies beyond, utilising a vast array of metaphysical abilities and artifacts to protect the Marvel Cinematic Universe.", "2h 10m", "Fantasy", {"12:00", "15:00", "18:00", "21:00"}, 15.0)
     };

    vector<Movie> comingSoon = {
        Movie("Avatar 2", "Synopsis of Avatar 2", "2h 45m", "Sci-Fi", {"10:00", "13:00", "16:00", "19:00"}, 20.0),
        Movie("Inside Out 2", "Teenager Riley's mind headquarters is undergoing a sudden demolition to make room for something entirely unexpected: new Emotions. Joy, Sadness, Anger, Fear and Disgust, who've long been running a successful operation by all accounts, aren't sure how to feel when Anxiety shows up. And it looks like she's not alone", "1h 36m", "Animation", {"10:00", "13:00", "16:00", "19:00"}, 20.0),
    };

    vector<Theater> theaters = {
        Theater("Cinema XXI", {
            Movie("The Batman", "Two years of nights have turned Bruce Wayne into a nocturnal animal. But as he continues to find his way as Gotham's dark knight Bruce is forced into a game of cat and mouse with his biggest threat so far, a manic killer known as 'The Riddler' who is filled with rage and determined to expose the corrupt system whilst picking off all of Gotham's key political figures. Working with both established and new allies, Bruce must track down the killer and see him brought to justice, while investigating his father's true legacy and questioning the effect that he has had on Gotham so far as 'The Batman.'", "2h 55m", "Action", {"10:00", "13:00", "16:00", "19:00"}, 10.0),
            Movie("Spider-Man: No Way Home", "Peter Parker's secret identity is revealed to the entire world. Desperate for help, Peter turns to Doctor Strange to make the world forget that he is Spider-Man. The spell goes horribly wrong and shatters the multiverse, bringing in monstrous villains that could destroy the world.", "2h 30m", "Action", {"11:00", "14:00", "17:00", "20:00"}, 12.0)
        }),
        Theater("CGV", {
            Movie("The Batman", "Two years of nights have turned Bruce Wayne into a nocturnal animal. But as he continues to find his way as Gotham's dark knight Bruce is forced into a game of cat and mouse with his biggest threat so far, a manic killer known as 'The Riddler' who is filled with rage and determined to expose the corrupt system whilst picking off all of Gotham's key political figures. Working with both established and new allies, Bruce must track down the killer and see him brought to justice, while investigating his father's true legacy and questioning the effect that he has had on Gotham so far as 'The Batman.'", "2h 55m", "Action", {"10:00", "13:00", "16:00", "19:00"}, 10.0),
            Movie("Doctor Strange in the Multiverse of Madness", "Marvel's 'Doctor Strange' follows the story of the talented neurosurgeon Doctor Stephen Strange who, after a tragic car accident, must put ego aside and learn the secrets of a hidden world of mysticism and alternate dimensions. Based in New York City's Greenwich Village, Doctor Strange must act as an intermediary between the real world and what lies beyond, utilising a vast array of metaphysical abilities and artifacts to protect the Marvel Cinematic Universe.", "2h 10m", "Fantasy", {"12:00", "15:00", "18:00", "21:00"}, 15.0)
        })
    };

    vector<User> users = {
        User("user1", "password1"),
        User("user2", "password2")
    };

    CinemaSystem cinemaSystem(theaters, playingNow, comingSoon, users);
    cinemaSystem.run();

    return 0;
}

