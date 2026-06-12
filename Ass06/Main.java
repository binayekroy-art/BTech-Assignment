import java.util.*;
import java.util.stream.*;

class Student {
    int id;
    String name;
    List<String> courses;
    Map<String, Integer> scores;

    public Student(int id, String name, List<String> courses, Map<String, Integer> scores) {
        this.id = id;
        this.name = name;
        this.courses = courses;
        this.scores = scores;
    }

    public double getAverageScore() {
        return scores.values().stream()
                .mapToInt(Integer::intValue)
                .average()
                .orElse(0.0);
    }
}

class StudentAnalyzer {
    public static List<Student> getTopNStudents(List<Student> students, int n) {
        return students.stream()
                .sorted(Comparator.comparingDouble(Student::getAverageScore).reversed())
                .limit(n)
                .collect(Collectors.toList());
    }

    public static Map<String, Double> getAverageScorePerCourse(List<Student> students) {
        Map<String, List<Integer>> courseScores = new HashMap<>();
        for (Student student : students) {
            for (String course : student.courses) {
                int score = student.scores.getOrDefault(course, 0);
                courseScores.computeIfAbsent(course, k -> new ArrayList<>()).add(score);
            }
        }
        Map<String, Double> averageScores = new HashMap<>();
        for (String course : courseScores.keySet()) {
            double avg = courseScores.get(course).stream()
                    .mapToInt(Integer::intValue)
                    .average()
                    .orElse(0.0);
            averageScores.put(course, avg);
        }
        return averageScores;
    }

    public static Set<String> getAllUniqueCourses(List<Student> students) {
        return students.stream()
                .flatMap(student -> student.courses.stream())
                .collect(Collectors.toSet());
    }
}
