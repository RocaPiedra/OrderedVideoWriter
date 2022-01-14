#include <string>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>

#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

#define DEFAULT_INPUT_PATH "/home/nvidia/repos/APPIDE/vidtest/RGB/IMAGES/1024x1024/"
#define DEFAULT_OUTPUT_PATH "../WrittenVideos/Video.avi"
#define DEFAULT_FPS 30
#define DEFAULT_CODEC VideoWriter::fourcc('M', 'J', 'P', 'G')


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

int main(int argc, char *argv[])
{
    const char* input_path;
    string output_path;
    double fps;

    if (argc == 4){
        input_path = argv[1];
        cout << "Input path introduced is: " << input_path << endl;
        output_path = string(argv[2]);
        cout << "Output path introduced is: " << output_path << endl;
        fps = atof(argv[3]); // framerate of the created video stream
        cout << "FPS introduced is: " << fps << endl;        
    } else if (argc == 3 ){
        input_path = argv[1];
        cout << "Input path introduced is: " << input_path << endl;
        output_path = string(argv[2]);
        cout << "Output path introduced is: " << output_path << endl;
        fps = DEFAULT_FPS; // framerate of the created video stream
        cout << "FPS not defined, selected default FPS: " << fps << endl;
    } else if(argc == 2){
        input_path = argv[1];
        cout << "Input path introduced is: " << input_path << endl;
        output_path = DEFAULT_OUTPUT_PATH;
        cout << "Output path not defined, selected default path: " << output_path << endl;
        fps = DEFAULT_FPS; // framerate of the created video stream
        cout << "FPS not defined, selected default value: " << fps << endl;
    }
    else{
        input_path = DEFAULT_INPUT_PATH;
        output_path = DEFAULT_OUTPUT_PATH;
        fps = DEFAULT_FPS; // framerate of the created video stream
        cout << "Input, output and FPS not defined, selected default options:" << endl;
        cout << "Input path: " << input_path << endl;
        cout << "Output path: " << output_path << endl;
        cout << "FPS: " << fps << endl;
        
    }

    int codec = DEFAULT_CODEC;  // select desired codec (must be available at runtime)
    bool visualize = false;
    VideoGenerator(input_path, output_path, codec, fps, visualize);

    return 0;
}