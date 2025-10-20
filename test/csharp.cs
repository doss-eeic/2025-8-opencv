using System.Runtime.InteropServices;
using cv;



namespace OpenCvCSharp {
    class CvTest {
        static void Main()
        {
            cv.VideoCapture cap(0);
            if (!cap.isOpened())
            {
                Console.WriteLine("カメラを開けませんでした");
                throw new Exception("カメラを開けませんでした");
                return;
            }

            while (true)
            {
                cv.Mat frame = cap.read();
                if (frame.empty())
                {
                    Console.WriteLine("フレームを読み取れませんでした");
                    break;
                }
                cv2.imshow("frame", frame);
                if (cv.waitKey(1) == 27)
                {
                    break;
                }
                if(cv.waitKey(1) == 'q')
                {
                    Console.WriteLine("ユーザーによって終了されました\n");
                    break;
                }
            }

            cap.release();
            cv.destroyAllWindows();
        }
    }
}