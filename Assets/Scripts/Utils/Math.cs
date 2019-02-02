namespace Utils {
    public static class Math
    {
        public static float Map(float value, float from, float to, float onFrom, float onTo) {
            if (value <= from) {
                return onFrom;
            } else if(value >= to) {
                return onTo;
            } else {
                return (onTo - onFrom) * ((value - from) / (to - from)) + onFrom;
            }
        }
    }
}