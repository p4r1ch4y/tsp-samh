#include <bits/stdc++.h>
using namespace std;

// City structure
struct City {
    int id;       // Unique ID of the city
    double x, y;  // Coordinates of the city
};

// Euclidean distance between two citie
double distance ( const City& a, const City& b ) {
    return sqrt ( pow ( a.x - b.x, 2) + pow ( a.y - b.y, 2));
}

// Function to calculate the total length of a tour
double tourLength ( const vector<City>& cities, const vector<int>& tour ) {
    double total = 0.0;
    for ( size_t i = 0; i < tour.size(); ++i ) {
        int current = tour[i];
        int next = tour [( i + 1 ) % tour.size()]; // Wrap around to the first city
        total += distance ( cities[current], cities[next] );
    }
    return total;
}

// Function to randomly swap two cities in the tour
vector<int> swapCities ( const vector<int>& tour, mt19937& gen ) {
    vector<int> newTour = tour;
    uniform_int_distribution<> dis ( 0, tour.size() - 1 );
    int i = dis ( gen ), j = dis ( gen );
    while ( i == j ) j = dis ( gen ); // Ensure two different indices
    swap ( newTour[i], newTour[j] );
    return newTour;
}

// Function to read city data from a file
vector<City> readCities ( const string& filename ) {
    vector<City> cities;
    ifstream file ( filename );
    if ( !file ) {
        cerr << "Error: Uhh Oh! Unable to open file: " << filename << endl;
        return cities;
    }

    string line;
    bool readingCities = false;

    // Parse the file to extract city data
    while ( getline ( file, line ) ) {
        if ( line.find ( "NODE_COORD_SECTION" ) != string::npos) {
            readingCities = true;
            continue;
        }
        if  ( line.find ( "EOF" ) != string::npos ) break;
        if ( readingCities ) {
            City city;
            istringstream iss ( line );
            iss >> city.id >> city.x >> city.y;
            city.id--; // Convert to 0-based indexing
            cities.push_back(city);
        }
    }
    return cities;
}

// Simulated Annealing algorithm to find the best tour
vector<int> findBestTour ( const vector<City>& cities, double startTemp, double coolRate, int numIterations ) {
    vector<int> tour ( cities.size () );
    iota (tour.begin (), tour.end (), 0 ); // Initialize tour with city indices

    random_device rd;
    mt19937 gen (rd () );
    shuffle ( tour.begin(), tour.end(), gen ); // Randomize initial tour

    vector<int> bestTour = tour;
    double currentLength = tourLength ( cities, tour );
    double bestLength = currentLength;
    double temp = startTemp;

    uniform_real_distribution<> dis ( 0.0, 1.0 );

    // Main loop for simulated annealing
    for ( int i = 0; i < numIterations; ++i ) {
        vector<int> newTour = swapCities ( tour, gen );
        double newLength = tourLength ( cities, newTour );
        double delta = newLength - currentLength;

        // Accept new tour based on probability or improvement
        if ( delta < 0 || dis ( gen ) < exp ( -delta / temp )) {
            tour = newTour;
            currentLength = newLength;
            if ( currentLength < bestLength ) {
                bestTour = tour;
                bestLength = currentLength;
            }
        }

        temp *= coolRate; // Gradually reduce temperature

        // Log progress every 1000 iterations
        if ( i % 1000 == 0 ) {
            cout << "Iteration " << i << ": Best length = " << bestLength << endl;
        }
    }

    return bestTour;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <tsp_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    vector<City> cities = readCities (  filename );

    if (cities.empty()) {
        cerr << "Error: No cities found in the file." << endl;
        return 1;
    }

    cout << "Loaded " << cities.size() << " cities from " << filename << endl;

    // simulated annealing parameters
    // These parameters can be adjusted for better performance
    double startTemp = 10000.0;
    double coolRate = 0.99995;
    int numIterations = 10000;

    cout << "Starting Simulated Annealing with:" << endl;
    cout << "  Start Temperature: " << startTemp << endl;
    cout << "  Cooling Rate: " << coolRate << endl;
    cout << "  Iterations: " << numIterations << endl;

    // Measures execution time
    auto start = chrono::high_resolution_clock::now();
    vector<int> bestTour = findBestTour ( cities, startTemp, coolRate, numIterations );
    auto end = chrono::high_resolution_clock::now();

    double bestLength = tourLength ( cities, bestTour );

    // Output the results
    cout << "\nBest Tour Length: " << bestLength << endl;
    cout << "Best Tour: ";
    for ( int city : bestTour ) cout << city + 1 << " "; // Converts back to 1-based indexing
    cout << endl;

    chrono::duration<double> timeTaken = end - start;
    cout << "Time Taken: " << timeTaken.count() << " seconds" << endl;

    return 0;
}