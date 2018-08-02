package org.suirui.srpaas.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.view.View;

public class ScreenShot {
	// 获取指定Activity的截屏，保存到png文件
	public static Bitmap takeScreenShot(Activity activity, int x, int y,
			int right, int bottom) {
		// View是你需要截图的View
		View view = activity.getWindow().getDecorView();
		view.setDrawingCacheEnabled(true);
		view.buildDrawingCache();
		Bitmap b1 = view.getDrawingCache();
		// 获取状态栏高度
		Rect frame = new Rect();
		activity.getWindow().getDecorView().getWindowVisibleDisplayFrame(frame);
		int statusBarHeight = frame.top;
		// 获取屏幕长和高
		int width = activity.getWindowManager().getDefaultDisplay().getWidth();
		int height = activity.getWindowManager().getDefaultDisplay()
				.getHeight();
		// 去掉标题栏
		// Bitmap b = Bitmap.createBitmap(b1, 0, 25, 320, 455);
		Bitmap b = Bitmap.createBitmap(b1, x, statusBarHeight + y, width - x
				- right - right, height - (statusBarHeight + y) - bottom);
		view.destroyDrawingCache();
		return b;
	}

	// 保存到sdcard
	public static void savePic(Bitmap b, String strFilePathName) {
		File f = new File(strFilePathName);
		if (!f.exists()) {
			try {
				f.createNewFile();
			} catch (IOException e) {
			}
		}
		FileOutputStream fos = null;
		try {
			fos = new FileOutputStream(strFilePathName);
			if (null != fos) {
				b.compress(Bitmap.CompressFormat.PNG, 90, fos);
				fos.flush();
				fos.close();
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
