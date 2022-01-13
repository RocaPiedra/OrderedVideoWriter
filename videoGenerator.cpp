#include <string>
#include <iostream>
#include <dirent.h>

#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int VideoGenerator(const char *input_path, string output_path, int codec, double fps, bool show)
{
    DIR *dir = opendir(input_path);
    struct dirent *entry;
    char *imageName;
    string input_name;
    Mat image;
    int counter = 0;
    vector<string> path_vector; //vector storing all paths to sort
    
    while ((entry = readdir(dir)) != NULL)
    {
        imageName = entry->d_name;
        if (strcmp(imageName, ".") != 0 && strcmp(imageName, "..") != 0) // Check image name to avoid '.' and '..' entries
        {  
            input_name = string(input_path) + string(imageName);
            path_vector.push_back(input_name);
            counter++;
        }
        if(show){destroyAllWindows();}    
    }

    sort(path_vector.begin(), path_vector.end()); //Sorts the vector to maintain a natural writing order

    string videoName = "video_ordered";
    string extension = ".avi";
    Mat req_image = imread(input_name); //Take a sample image to obtain the size, input it manually if you want an specific resolution
    bool isColor = (req_image.type() == CV_8UC3);
    cout << "image size is " << req_image.size() << endl;

    VideoWriter writer;
    
    writer.open(output_path, codec, fps, req_image.size(), isColor);
    
    if ( !writer.isOpened())
    {
        cout  << "Could not open the input video." << input_path << endl;
        return -1;
    }
    cout << "Writing videofile: " << output_path << endl;
    if(show){namedWindow("Live_writer",cv::WINDOW_AUTOSIZE);}

    for(auto i : path_vector)    {
        cout << "path is "<< i << endl;
        image = imread(i);
        if(show){imshow("Live_writer",image);}
        if(show){waitKey(300);}
        writer.write(image);
    }
    
    cout << "A total of " << counter << " images have been written in " << output_path << endl;
    return 0;
}

int main(void)
{
    const char* input_path = "/home/nvidia/repos/APPIDE/vidtest/RGB/IMAGES/1024x1024/";
    string output_path = "../Video.avi";
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    double fps = 30;  // framerate of the created video stream
    bool visualize = false;
    VideoGenerator(input_path, output_path, codec, fps, visualize);

    return 0;
}