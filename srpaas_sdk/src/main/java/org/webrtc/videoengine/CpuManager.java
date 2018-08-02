package org.webrtc.videoengine;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class CpuManager {
 
        // 获取CPU最大频率（单位KHZ）
     // "/system/bin/cat" 命令行
     // "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq" 存储最大频率的文件的路径
        public static String getMaxCpuFreq() {
                String result = "";
                ProcessBuilder cmd;
                try {
                        String[] args = { "/system/bin/cat",
                                        "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq" };
                        cmd = new ProcessBuilder(args);
                        Process process = cmd.start();
                        InputStream in = process.getInputStream();
                        byte[] re = new byte[24];
                        while (in.read(re) != -1) {
                                result = result + new String(re);
                        }
                        in.close();
                } catch (IOException ex) {
                        ex.printStackTrace();
                        result = "N/A";
                }
                return result.trim();
        }
 
         // 获取CPU最小频率（单位KHZ）
        public static String getMinCpuFreq() {
                String result = "";
                ProcessBuilder cmd;
                try {
                        String[] args = { "/system/bin/cat",
                                        "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq" };
                        cmd = new ProcessBuilder(args);
                        Process process = cmd.start();
                        InputStream in = process.getInputStream();
                        byte[] re = new byte[24];
                        while (in.read(re) != -1) {
                                result = result + new String(re);
                        }
                        in.close();
                } catch (IOException ex) {
                        ex.printStackTrace();
                        result = "N/A";
                }
                return result.trim();
        }
 
         // 实时获取CPU当前频率（单位KHZ）
        public static String getCurCpuFreq() {
                String result = "N/A";
                try {
                        FileReader fr = new FileReader(
                                        "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
                        BufferedReader br = new BufferedReader(fr);
                        String text = br.readLine();
                        result = text.trim();
                } catch (FileNotFoundException e) {
                        e.printStackTrace();
                } catch (IOException e) {
                        e.printStackTrace();
                }
                return result;
        }
 
        // 获取CPU名字
        public static String getCpuName() {
                try {
                        FileReader fr = new FileReader("/proc/cpuinfo");
                        BufferedReader br = new BufferedReader(fr);
                        String text = br.readLine();
                        String[] array = text.split(":\\s+", 2);
                        for (int i = 0; i < array.length; i++) {
                        }
                        return array[1];
                } catch (FileNotFoundException e) {
                        e.printStackTrace();
                } catch (IOException e) {
                        e.printStackTrace();
                }
                return null;
        }
        
        /*
        private String getCpuUsage() {

        	  ProcessBuilder cmd;

        	  String result = "";

        	  

        	//获得CPU 使用率，采用正则表达式分析字符串信息
        	  String Result;
        	  Process p=Runtime.getRuntime().exec("top -n 1");
        	  BufferedReader br=new BufferedReader(new InputStreamReader(p.getInputStream()));
        	  //buffer =          new BufferedReader(new InputStreamReader(urlconn.getInputStream()));
        	  
        	  while((Result=br.readLine())!=null)
        	  {
        		  if(Result.trim().length()<1){
        			  continue;
        		  }else{
		        	  String[] CPUusr = Result.split("%");
		        	  
		        	  tv.append("USER:"+CPUusr[0]+"\n");
		        	  String[] CPUusage = CPUusr[0].split("User");
		        	  String[] SYSusage = CPUusr[1].split("System");
		        	  tv.append("CPU:"+CPUusage[1].trim()+" length:"+CPUusage[1].trim().length()+"\n");
		        	  tv.append("SYS:"+SYSusage[1].trim()+" length:"+SYSusage[1].trim().length()+"\n");
		        	  tv.append(Result+"\n");
		        	  break;
        	  }
      }
        */
	  public static float getProcessCpuRate()
	   {
	        
	       float totalCpuTime1 = getTotalCpuTime();
	       float processCpuTime1 = getAppCpuTime();
	       try
	       {
	           Thread.sleep(360);
	            
	       }
	       catch (Exception e)
	       {
	       }
	        
	       float totalCpuTime2 = getTotalCpuTime();
	       float processCpuTime2 = getAppCpuTime();
	        
	       float cpuRate = 100 * (processCpuTime2 - processCpuTime1)
	               / (totalCpuTime2 - totalCpuTime1);
	        
	       return cpuRate;
	   }
	    
	   public static long getTotalCpuTime()
	   { // 获取系统总CPU使用时间
	       String[] cpuInfos = null;
	       try
	       {
	           BufferedReader reader = new BufferedReader(new InputStreamReader(
	                   new FileInputStream("/proc/stat")), 1000);
	           String load = reader.readLine();
	           reader.close();
	           cpuInfos = load.split(" ");
	       }
	       catch (IOException ex)
	       {
	           ex.printStackTrace();
	       }
	       long totalCpu = Long.parseLong(cpuInfos[2])
	               + Long.parseLong(cpuInfos[3]) + Long.parseLong(cpuInfos[4])
	               + Long.parseLong(cpuInfos[6]) + Long.parseLong(cpuInfos[5])
	               + Long.parseLong(cpuInfos[7]) + Long.parseLong(cpuInfos[8]);
	       return totalCpu;
	   }
	    
	   public static long getAppCpuTime()
	   { // 获取应用占用的CPU时间
	       String[] cpuInfos = null;
	       try
	       {
	           int pid = android.os.Process.myPid();
	           BufferedReader reader = new BufferedReader(new InputStreamReader(
	                   new FileInputStream("/proc/" + pid + "/stat")), 1000);
	           String load = reader.readLine();
	           reader.close();
	           cpuInfos = load.split(" ");
	       }
	       catch (IOException ex)
	       {
	           ex.printStackTrace();
	       }
	       long appCpuTime = Long.parseLong(cpuInfos[13])
	               + Long.parseLong(cpuInfos[14]) + Long.parseLong(cpuInfos[15])
	               + Long.parseLong(cpuInfos[16]);
	       return appCpuTime;
	   } 
       
	   public static String getCpuUsage()
	   {
		   String Result;
	        Process p = null;
			try {
				p = Runtime.getRuntime().exec("top -n 1");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

	        BufferedReader br=new BufferedReader(new InputStreamReader   
	        (p.getInputStream ()));
	        try {
				while((Result=br.readLine())!=null)
				{
				    if(Result.trim().length()<1){
				    continue;
				    }else{
				    	String[] CPUusr = Result.split("%");
				        String[] CPUusage = CPUusr[0].split("User");
				        String[] SYSusage = CPUusr[1].split("System");
				        //String user_cpu;
				        //user_cpu = String.format("CPU:"+CPUusage[1].trim()+" length:"+CPUusage[1].trim().length()+"\n");
				        //String system_cpu;
				        //system_cpu = String.format("SYS:"+SYSusage[1].trim()+" length:"+SYSusage[1].trim().length()+"\n");
				        //tv.append(Result+"\n");
				        String cpu_usage;
				        cpu_usage = String.format("CPU:"+CPUusage[1].trim()+" length:"+CPUusage[1].trim().length()+"SYS:"+SYSusage[1].trim()+" length:"+SYSusage[1].trim().length());
				        return cpu_usage;
				        
				    //    break;
				    }
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return null; 
	       
	   }
	   
	   
	   public static String getProcessName()
	   {
		   String Result;
		   String cpuName = null;
	        Process p = null;
			try {
				p = Runtime.getRuntime().exec("cat /proc/cpuinfo");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

	        BufferedReader br=new BufferedReader(new InputStreamReader   
	        (p.getInputStream ()));
	        try {
				while((Result=br.readLine())!=null)
				{
				    if(Result.trim().length()<1){
				    continue;
				    }else{
				    	String chipName = "Hardware";
				    	int idx = Result.indexOf(chipName);
				        if (idx >= 0) {
				        	cpuName = Result.substring(idx);
				        	String[] cpuNameStr = cpuName.split(":");
				        	return cpuNameStr[1].trim().toUpperCase();
				        }
				    }
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return null; 
	   }
	   
	   public static String GetSystemInfo()
	   {
		   String phoneInfo = "Product: " + android.os.Build.PRODUCT;
	        phoneInfo += ", CPU_ABI: " + android.os.Build.CPU_ABI;
	        phoneInfo += ", TAGS: " + android.os.Build.TAGS;
	        phoneInfo += ", VERSION_CODES.BASE: " + android.os.Build.VERSION_CODES.BASE;
	        phoneInfo += ", MODEL: " + android.os.Build.MODEL;
	        phoneInfo += ", VERSION.RELEASE: " + android.os.Build.VERSION.RELEASE;
	        phoneInfo += ", DEVICE: " + android.os.Build.DEVICE;
	        phoneInfo += ", DISPLAY: " + android.os.Build.DISPLAY;
	        phoneInfo += ", BRAND: " + android.os.Build.BRAND;
	        phoneInfo += ", BOARD: " + android.os.Build.BOARD;
	        phoneInfo += ", FINGERPRINT: " + android.os.Build.FINGERPRINT;
	        phoneInfo += ", ID: " + android.os.Build.ID;
	        phoneInfo += ", MANUFACTURER: " + android.os.Build.MANUFACTURER;
	        phoneInfo += ", USER: " + android.os.Build.USER;
	        // Toast.makeText(this, phoneInfo, Toast.LENGTH_LONG).show();
	        
	        return phoneInfo;
	   }
        
        
}
 