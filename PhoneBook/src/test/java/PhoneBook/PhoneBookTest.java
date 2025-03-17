package PhoneBook;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

public class PhoneBookTest {

  @Test
  @Timeout(310)
  @DisplayName("PhoneBook consists of valid 100_000 entries")
  public void Test_PhoneBook_1() {
    PhoneBook pb = new PhoneBook();
    pb.setUpdateIntervalM(4);
    pb.setTotalDurationT(62);
    pb.start();

    Map<String, String> currentPhoneBook = pb.getResultPhoneBook();
    assertNotNull(currentPhoneBook);
    assertEquals(100_000, currentPhoneBook.size());
    currentPhoneBook.forEach(
        (key, value) -> {
          assertTrue(key.startsWith("aminaall"));

          assertTrue(value.startsWith("+7"));

          assertEquals(
              12,
              value.length(),
              "Номер телефона после +7: '" + value + "' должен содержать ровно 10 цифр");

          String digits = value.substring(2);
          assertTrue(
              digits.matches("\\d{10}"),
              "Номер телефона после +7: '" + value + "' должен состоять только из цифр");
        });
  }
}
