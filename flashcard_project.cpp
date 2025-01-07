#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

struct Flashcard {
    std::string question;
    std::string answer;
    int timesIncorrect; // Tracks how often the card was marked incorrect
};

class FlashcardSystem {
private:
    std::vector<Flashcard> cards; // Stores the flashcards

    bool isDuplicate(const std::string& question, const std::string& answer) {
        for (const auto& card : cards) {
            if (card.question == question && card.answer == answer) {
                return true;
            }
        }
        return false;
    }

public:
    void addFlashcard(const std::string& question, const std::string& answer);
    void reviewFlashcards(bool shuffle = false);
    void deleteFlashcard();
};

void FlashcardSystem::addFlashcard(const std::string& question, const std::string& answer) {
    if (isDuplicate(question, answer)) {
        std::cout << "Duplicate flashcard not added. A flashcard with the same question and answer already exists.\n";
        return;
    }

    Flashcard newCard = {question, answer, 0};
    cards.push_back(newCard);
    std::cout << "Flashcard added!\n";
}

void FlashcardSystem::reviewFlashcards(bool shuffle) {
    if (cards.empty()) {
        std::cout << "No flashcards to review.\n";
        return;
    }

    if (shuffle) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        std::random_shuffle(cards.begin(), cards.end());
    }

    for (auto& card : cards) {
        std::cout << "\nQuestion: " << card.question << "\n";
        std::string userAnswer;
        std::cout << "Your Answer: ";
        std::getline(std::cin, userAnswer);

        if (userAnswer == card.answer) {
            std::cout << "Correct!\n";
        } else {
            std::cout << "Incorrect! The correct answer is: " << card.answer << "\n";
            card.timesIncorrect++;
        }
    }
}

void FlashcardSystem::deleteFlashcard() {
    if (cards.empty()) {
        std::cout << "No flashcards available to delete.\n";
        return;
    }

    std::cout << "\n--- Flashcards ---\n";
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << i + 1 << ". " << cards[i].question << "\n";
    }

    std::cout << "Enter the number of the flashcard to delete: ";
    int index;
    if (!(std::cin >> index) || index < 1 || index > static_cast<int>(cards.size())) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid choice. Please enter a valid number.\n";
        return;
    }

    cards.erase(cards.begin() + (index - 1));
    std::cout << "Flashcard deleted!\n";
    std::cin.ignore(); // Clear the newline character from the input stream
}

int main() {
    FlashcardSystem system;
    int choice;

    do {
        std::cout << "\n--- Flashcard System Menu ---\n";
        std::cout << "1. Add Flashcard\n";
        std::cout << "2. Review Flashcards\n";
        std::cout << "3. Delete Flashcard\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Please enter a valid input.\n";
            continue; // Prompt the menu again
        }

        std::cin.ignore(); // Ignore newline after number input

        switch (choice) {
        case 1: {
            std::string question, answer;
            std::cout << "Enter Question: ";
            std::getline(std::cin, question);
            std::cout << "Enter Answer: ";
            std::getline(std::cin, answer);
            system.addFlashcard(question, answer);
            break;
        }
        case 2:
            system.reviewFlashcards(true); // Shuffle cards during review
            break;
        case 3:
            system.deleteFlashcard();
            break;
        case 4:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Please enter a valid input.\n";
        }
    } while (choice != 4);

    return 0;
}
