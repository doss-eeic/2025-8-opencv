using System;
using System.Runtime.InteropServices;

namespace OpenCvCSharp {
    class CvTest {

        // csharp_wrapperディレクトリの機能を直接使用
        private const string OPENCV_DLL = "libopencv_csharp_wrapper.dylib";

        // csharp_wrapperの関数を直接呼び出し
        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int opencv_camera_simple_test(int device, [MarshalAs(UnmanagedType.LPStr)] string winname);

        static void Main()
        {
            try
            {
                Console.WriteLine("============================================================");
                Console.WriteLine("OpenCV C# カメラテスト (csharp_wrapper直接使用)");
                Console.WriteLine("============================================================");
                Console.WriteLine("csharp_wrapperディレクトリの機能を直接使用してカメラテストを実行中...");
                Console.WriteLine("終了するにはESCキーまたは'q'キーを押してください");
                Console.WriteLine();
                
                // csharp_wrapperの機能を直接呼び出し
                int result = opencv_camera_simple_test(0, "OpenCV C# Wrapper Test");

                if (result == 1)
                {
                    Console.WriteLine("✅ カメラテストが正常に完了しました");
                    Console.WriteLine("csharp_wrapperディレクトリの機能が正常に動作しました");
                }
                else
                {
                    Console.WriteLine("❌ カメラテストが失敗しました");
                }
                
            }
            catch (Exception ex)
            {
                Console.WriteLine($"エラーが発生しました: {ex.Message}");
            }
        }
    }
}