#include <curl/curl.h>
#include <iostream>
#include <string>

// Callback function to write the API response to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    output->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

int main()
{
    // Initialize cURL
    CURL* curl = curl_easy_init();

    if (curl)
    {
        // Set the Binance API endpoint URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT");

        // Set callback function to receive API response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        std::string apiResponse;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);

        // Perform the HTTP GET request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) { std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl; }
        else
        {
            std::cout << "API Response:\n" << apiResponse << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    else
    {
        std::cerr << "Failed to initialize cURL." << std::endl;
    }

    return EXIT_SUCCESS;
}
