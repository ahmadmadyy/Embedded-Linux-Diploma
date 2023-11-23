#include <iostream>
#include <algorithm>
#include <vector>

class SortStrategy
{
    public:
        virtual void sort() = 0;
        virtual ~SortStrategy() = default;
};

struct Record
{
    public:
        Record(std::string m_name,int m_id, SortStrategy *m_strategy)
                                : name(m_name), id(m_id), strategy(m_strategy)
        {

        }
        void sort()
        {
            strategy->sort();
        }

        std::string name;
        int id;
        SortStrategy *strategy;

};

struct comp_by_name 
{
    bool operator()(const Record& a, const Record& b) const {
        return a.name < b.name;
    }
};

struct comp_by_id 
{
    bool operator()(const Record& a, const Record& b) const {
        return a.id < b.id;
    }
};

class InsertionSort : public SortStrategy 
{
private:
    std::vector<Record>& records;

public:
    InsertionSort(std::vector<Record>& r) : records(r) {}

    void sort() override 
    {
        int n = records.size();
        for (int i = 1; i < n; ++i) {
            Record key = records[i];
            int j = i - 1;

            while (j >= 0 && comp_by_name()(records[j], key)) 
            {
                records[j + 1] = records[j];
                --j;
            }
            records[j + 1] = key;
        }
    }
};


class SelectionSort : public SortStrategy 
{
private:
    std::vector<Record>& records;

public:
    SelectionSort(std::vector<Record>& r) : records(r) {}

    void sort() override {
        int n = records.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (comp_by_id()(records[j], records[minIndex])) {
                    minIndex = j;
                }
            }
            std::swap(records[i], records[minIndex]);
        }
    }
};



int main()
{
    std::vector<Record> records = {
        {"Ahmed", 3, nullptr},
        {"Mohamed", 1, nullptr},
        {"Ali", 2, nullptr}
    };

    while(1)
    {

        // Ask the user to choose the sorting algorithm
        std::cout << "Choose sorting algorithm (1 >> Insertion Sort, 2 >> Selection Sort): ";
        int algorithmChoice;
        std::cin >> algorithmChoice;

        SortStrategy* sortingStrategy = nullptr;

        // Set the sorting strategy based on user input
        if (algorithmChoice == 1) 
        {
            sortingStrategy = new InsertionSort(records);
        } 
        else if (algorithmChoice == 2) 
        {
            sortingStrategy = new SelectionSort(records);
        } 
        else 
        {
            std::cout << "Invalid choice. Exiting.\n";
            return 1;
        }

        // Ask the user to choose the sorting criteria
        std::cout << "Choose sorting criteria (1 for Name, 2 for ID): ";
        int criteriaChoice;
        std::cin >> criteriaChoice;

        // Set the comparison functor based on user input
        if (criteriaChoice == 1) 
        {
            sortingStrategy->sort();
        } 
        else if (criteriaChoice == 2) 
        {
            for (auto& record : records) 
            {
                record.strategy = sortingStrategy;
            }
            // Sort by ID using the chosen sorting algorithm
            for (auto& record : records) 
            {
                record.sort();
            }
        } 
        else 
        {
            std::cout << "Invalid choice. Exiting.\n";
            return 1;
        }

        // Output the sorted records
        std::cout << "Sorted records:\n";
        for (const auto& record : records) 
        {
            std::cout << "Name: " << record.name << ", ID: " << record.id << "\n";
        }

        // Clean up dynamically allocated sorting strategy
        delete sortingStrategy;
    }

    return 0;
}