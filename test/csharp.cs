using System;
using System.Runtime.InteropServices;
using VideoCapture = OpenCVSharp.VideoCapture;
using Mat = OpenCVSharp.Mat;
using CvSharp = OpenCVSharp.CvSharp;

namespace OpenCVSharp {
    class OpenCVSharpTest {
        static void Main() {
            Console.WriteLine("================================================");
            Console.WriteLine("OpenCV C# camera test");
            Console.WriteLine("================================================");
            Console.WriteLine("Using the functions directly from the csharp_wrapper directory");
            Console.WriteLine("Press ESC or 'q' to exit");
            Console.WriteLine();
            
            using (VideoCapture cap = new VideoCapture(0)) {
                if (!cap.IsOpened()) {
                    throw new Exception("❌ Camera cannot be opened");
                }

                using (Mat frame = new Mat()) {
                    while (cap.Read(frame)) {
                        CvSharp.ImShow("OpenCV C# Wrapper Test", frame);
                        int key = CvSharp.WaitKey(1);
                        if (key == 'q' || key == 27) { // 27 is the ASCII code for ESC
                            break;
                        }
                        else if (key == 's') {
                            CvSharp.ImWrite("frame.jpg", frame);
                        }
                    }
                }
            }
            
            CvSharp.DestroyAllWindows();
            Console.WriteLine("================================================");
            Console.WriteLine("⭕️ Camera test successfully completed ✅");
            Console.WriteLine("================================================");
        }
    }
}