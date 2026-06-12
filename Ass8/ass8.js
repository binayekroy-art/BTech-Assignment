import React, { useState } from "react";

const CourseEnrollmentDashboard = () => {
  const [students, setStudents] = useState(
    new Map([
      [
        1,
        {
          id: 1,
          name: "Rahul",
          enrolledCourses: new Set(["Math", "Java", "DSA"]),
          gpa: 3.5,
        },
      ],
      [
        2,
        {
          id: 2,
          name: "Priya",
          enrolledCourses: new Set(["Math", "Java"]),
          gpa: 3.8,
        },
      ],
      [
        3,
        {
          id: 3,
          name: "Amit",
          enrolledCourses: new Set(["DSA", "AI"]),
          gpa: 3.9,
        },
      ],
    ])
  );

  const addStudent = (student) => {
    setStudents((prev) => new Map([...prev, [student.id, student]]));
  };

  const removeStudent = (id) => {
    setStudents((prev) => {
      const updated = new Map(prev);
      updated.delete(id);
      return updated;
    });
  };

  const sortedStudents = [...students.values()].sort(
    (a, b) => b.gpa - a.gpa
  );

  const allUniqueCourses = [
    ...sortedStudents.reduce(
      (acc, student) => new Set([...acc, ...student.enrolledCourses]),
      new Set()
    ),
  ];

  const filterByCourse = (course) =>
    sortedStudents.filter((student) => student.enrolledCourses.has(course));

  return (
    <div>
      <h2>Course Enrollment Dashboard</h2>

      <h3>Students (Sorted by GPA)</h3>
      <ul>
        {sortedStudents.map((s) => (
          <li key={s.id}>
            {s.name} (GPA: {s.gpa}) - Courses: {Array.from(s.enrolledCourses).join(", ")}
          </li>
        ))}
      </ul>

      <h3>All Unique Courses</h3>
      <ul>
        {allUniqueCourses.map((course, idx) => (
          <li key={idx}>{course}</li>
        ))}
      </ul>

      <h3>Filter Students by Course: "Java"</h3>
      <ul>
        {filterByCourse("Java").map((s) => (
          <li key={s.id}>
            {s.name} (GPA: {s.gpa})
          </li>
        ))}
      </ul>

      <button
        onClick={() =>
          addStudent({
            id: 4,
            name: "Sneha",
            enrolledCourses: new Set(["Math", "AI"]),
            gpa: 3.7,
          })
        }
      >
        Add Sneha
      </button>

      <button onClick={() => removeStudent(2)}>Remove Priya</button>
    </div>
  );
};

export default CourseEnrollmentDashboard;