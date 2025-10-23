 using System;
using System.Runtime.InteropServices;
 
 namespace OpenCVSharp {
    // C# wrapper classes that mirror the C++ classes
    public class VideoCapture : IDisposable {
        private IntPtr handle;
        private bool disposed = false;
        private const string OPENCV_DLL = "libopencv_csharp_wrapper.dylib";

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr cvsharp_videocapture_create(int device);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool cvsharp_videocapture_isopened(IntPtr cap);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool cvsharp_videocapture_read(IntPtr cap, IntPtr frame);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void cvsharp_videocapture_release(IntPtr cap);

        public VideoCapture(int device) {
            handle = cvsharp_videocapture_create(device);
        }

        public bool IsOpened() {
            return cvsharp_videocapture_isopened(handle);
        }

        public bool Read(Mat frame) {
            return cvsharp_videocapture_read(handle, frame.Handle);
        }

        public void Release() {
            if (handle != IntPtr.Zero) {
                cvsharp_videocapture_release(handle);
                handle = IntPtr.Zero;
            }
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (!disposed) {
                Release();
                disposed = true;
            }
        }

        ~VideoCapture() {
            Dispose(false);
        }
    }

    public class Mat : IDisposable {
        private IntPtr handle;
        private bool disposed = false;
        private const string OPENCV_DLL = "libopencv_csharp_wrapper.dylib";

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr cvsharp_mat_create();

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr cvsharp_mat_create_with_params(int rows, int cols, int type);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern int cvsharp_mat_get_rows(IntPtr mat);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern int cvsharp_mat_get_cols(IntPtr mat);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern int cvsharp_mat_get_type(IntPtr mat);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool cvsharp_mat_is_empty(IntPtr mat);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void cvsharp_mat_release(IntPtr mat);

        public IntPtr Handle => handle;

        public Mat() {
            handle = cvsharp_mat_create();
        }

        public Mat(int rows, int cols, int type) {
            handle = cvsharp_mat_create_with_params(rows, cols, type);
        }

        public int Rows => cvsharp_mat_get_rows(handle);
        public int Cols => cvsharp_mat_get_cols(handle);
        public int Type => cvsharp_mat_get_type(handle);
        public bool IsEmpty => cvsharp_mat_is_empty(handle);

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (!disposed) {
                if (handle != IntPtr.Zero) {
                    cvsharp_mat_release(handle);
                    handle = IntPtr.Zero;
                }
                disposed = true;
            }
        }

        ~Mat() {
            Dispose(false);
        }
    }

    public static class CvSharp {
        private const string OPENCV_DLL = "libopencv_csharp_wrapper.dylib";


        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "cvsharp_imshow")]
        public static extern void cvsharp_imshow(string windowName, IntPtr frame);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl, EntryPoint = "cvsharp_waitkey")]
        public static extern int cvsharp_waitkey(int delay);

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl, EntryPoint = "cvsharp_destroyallwindows")]
        public static extern void cvsharp_destroyallwindows();

        [DllImport(OPENCV_DLL, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "cvsharp_imwrite")]
        public static extern bool cvsharp_imwrite(string filename, IntPtr frame);

        public static void ImShow(string winname, Mat frame) {
            cvsharp_imshow(winname, frame.Handle);
        }

        public static int WaitKey(int delay) {
            return cvsharp_waitkey(delay);
        }

        public static void DestroyAllWindows() {
            cvsharp_destroyallwindows();
        }

        public static bool ImWrite(string filename, Mat frame) {
            return cvsharp_imwrite(filename, frame.Handle);
        }
    }
}