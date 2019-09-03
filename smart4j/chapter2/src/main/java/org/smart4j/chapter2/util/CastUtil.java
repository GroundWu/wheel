package org.smart4j.chapter2.util;

import org.apache.commons.lang3.StringUtils;

/**
 * 转型操作工具类
 */
public class CastUtil {
    /**
     * 转为String型
     */
    public static String castString(Object o){
        return CastUtil.castString(o,"");
    }

    private static String castString(Object o, String defaultVale) {
        return o!=null?String.valueOf(o):defaultVale;
    }

    /**
     * 转为double型
     */
    public static double castDouble(Object o){
        return CastUtil.castDouble(o,0);
    }

    private static double castDouble(Object o, double defaultValue) {
        double doubleValue=defaultValue;
        if(o!=null){
            String strValue=castString(o);
            if(StringUtil.isNotEmpty(strValue)){
                try{
                    doubleValue=Double.parseDouble(strValue);
                }catch (Exception e){
                    doubleValue=defaultValue;
                }
            }
        }
        return doubleValue;
    }


    /**
     *转为long
     */
    public static long castLong(Object o){
        return CastUtil.castLong(o,0);
    }

    private static long castLong(Object o, long defaultValue) {
        long longValue=defaultValue;
        if(o!=null){
            String strValue=castString(o);
            if(StringUtil.isNotEmpty(strValue)){
                try{
                    longValue=Long.parseLong(strValue);
                }catch (Exception e){
                    longValue=defaultValue;
                }
            }
        }
        return longValue;
    }

    public static int castInt(Object o) {
        return CastUtil.castInt(o,0);
    }

    private static int castInt(Object o, int defaultValue) {
        int intValue = defaultValue;
        if (o != null) {
            String strValue = castString(o);
            if (StringUtil.isNotEmpty(strValue)) {
                try {
                    intValue = Integer.parseInt(strValue);
                } catch (Exception e) {
                    intValue = defaultValue;
                }
            }
        }
        return intValue;
    }

    public static boolean castBoolean(Object o) {
        return CastUtil.castBoolean(o,false);
    }

    private static boolean castBoolean(Object o, boolean defaultValue) {
        boolean booleanValue = defaultValue;
        if(o!=null){
            booleanValue=Boolean.parseBoolean(castString(o));
        }
        return booleanValue;
    }
}
