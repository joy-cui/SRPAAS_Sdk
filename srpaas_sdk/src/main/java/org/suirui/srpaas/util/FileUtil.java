package org.suirui.srpaas.util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import android.os.Environment;

public class FileUtil {
	public static void writeFile(byte [] buf,String pathName,String fileName) throws IOException{   
		  try{   

		        File path = new File(pathName);  
			  File file = new File(pathName+fileName);
			  if( !path.exists()) {  
		            path.mkdir();  
		        }  
				  if(file.exists()){
					  //删除
					  file.delete();
				  }
		        if( !file.exists()) {  
	            file.createNewFile();  
		        }  
		        FileOutputStream stream = new FileOutputStream(file);  
		        stream.write(buf);            
		        stream.close();  
		 
		       
		      }   
		        catch(Exception e){  
		        e.printStackTrace();   
		  }   
		}
}
