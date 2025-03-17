package PhoneBook;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.*;

/**
 * Класс, записывающий 100 000 записей в справочник телефонных номеров (имя, номер телефона). Каждые
 * N миллисекунд у случайного кол-ва записей изменяется номер телефона. Через totalDurationT секунд
 * с момента начала программы в консоль выводятся записи, которые находились в справочнике
 * updateIntervalM секунд назад.
 */
public class PhoneBook {
  private final Random rand;
  private final int MAX_ENTRIES;
  private final int PHONE_NUMBER_LENGTH;
  private final int TASK_EXTRA_WAIT_TIME;
  private final int MIN_N;
  private final int MAX_N;
  private int updateIntervalM;
  private int totalDurationT;
  private final ConcurrentHashMap<String, String> newestPhoneBook;
  private Map<String, String> resultPhoneBook;
  private final String[] names;

  public PhoneBook() {
    rand = new Random();
    MAX_ENTRIES = 100_000;
    PHONE_NUMBER_LENGTH = 10;
    TASK_EXTRA_WAIT_TIME = 5;
    MIN_N = 501;
    MAX_N = 4999;
    final int MIN_M = 1;
    final int MAX_M = 29;
    final int MIN_T = 61;
    final int MAX_T = 299;
    updateIntervalM = rand.nextInt(MAX_M + 1 - MIN_M) + MIN_M;
    totalDurationT = rand.nextInt(MAX_T + 1 - MIN_T) + MIN_T;
    newestPhoneBook = new ConcurrentHashMap<>();
    resultPhoneBook = null;
    names = new String[MAX_ENTRIES];
  }

  public ConcurrentHashMap<String, String> getNewestPhoneBook() {
    return newestPhoneBook;
  }

  public Map<String, String> getResultPhoneBook() {
    return resultPhoneBook;
  }

  public void setUpdateIntervalM(int updateIntervalM) {
    this.updateIntervalM = updateIntervalM;
  }

  public void setTotalDurationT(int totalDurationT) {
    this.totalDurationT = totalDurationT;
  }

  public void start() {
    fillPhoneBook();
    System.out.println(
        "Параметры: updateIntervalM = "
            + updateIntervalM
            + " сек., totalDurationT = "
            + totalDurationT
            + " сек.");

    ExecutorService phoneWriterExecutor = Executors.newSingleThreadExecutor();
    Future<?> phoneWriterHandler = phoneWriterExecutor.submit(this::writePhoneNumbers);

    ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();
    scheduler.schedule(
        () -> savePhoneBook(phoneWriterExecutor, phoneWriterHandler),
        totalDurationT - updateIntervalM,
        TimeUnit.SECONDS);
    scheduler.schedule(this::printPhoneBook, totalDurationT, TimeUnit.SECONDS);
    shutdownExecutor(scheduler, totalDurationT + TASK_EXTRA_WAIT_TIME);
  }

  /** Первоначальное заполнение хэш-таблицы справочника */
  private void fillPhoneBook() {
    for (int i = 0; i < MAX_ENTRIES; i++) {
      String name = "aminaall" + i;
      names[i] = name;
      newestPhoneBook.put(name, randomPhoneNumber());
    }
  }

  /** Меняет случайное кол-во номеров телефона в справочнике на другие каждые N миллисекунд. */
  private void writePhoneNumbers() {
    while (!Thread.currentThread().isInterrupted()) {
      int n = rand.nextInt(MAX_N + 1 - MIN_N) + MIN_N;
      try {
        Thread.sleep(n);
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
        break;
      }
      int updateCount = rand.nextInt(MAX_ENTRIES + 1);
      for (int i = 0; i < updateCount; i++) {
        int index = rand.nextInt(names.length);
        String name = names[index];
        newestPhoneBook.put(name, randomPhoneNumber());
      }
    }
  }

  /**
   * Генерация случайного номера формата "+7XXXXXXXXXX" для справочника
   *
   * @return случайный номер
   */
  private String randomPhoneNumber() {
    StringBuilder sb = new StringBuilder();
    sb.append("+7");
    for (int i = 0; i < PHONE_NUMBER_LENGTH; i++) {
      sb.append(rand.nextInt(10));
    }
    return sb.toString();
  }

  /**
   * Сохраняет последнее изменение справочника в resultPhoneBook для дальнейшего вывода в sout.
   * Поскольку Executor обновления номеров более не нужен - останавливает поток
   */
  private void savePhoneBook(ExecutorService phoneWriterExecutor, Future<?> phoneWriterHandler) {
    resultPhoneBook = new HashMap<>(newestPhoneBook);
    System.out.printf(
        "Последняя версия справочника сохранена (прошло %d сек.).\n",
        totalDurationT - updateIntervalM);

    phoneWriterHandler.cancel(true);
    shutdownExecutor(phoneWriterExecutor, TASK_EXTRA_WAIT_TIME);
  }

  /** Вывод справочника, сохраненного updateIntervalM секунд назад */
  private void printPhoneBook() {
    System.out.printf("Вывод справочника, сохраненного %d сек. назад:\n", updateIntervalM);
    if (resultPhoneBook != null) {
      resultPhoneBook.forEach(
          (name, number) -> System.out.println("Name: " + name + ", Number: " + number));
    } else {
      System.out.println("Справочник не найден");
    }
  }

  /**
   * Завершение потока
   *
   * @param executor поток
   * @param waitTime время ожидания в секундах
   */
  private void shutdownExecutor(ExecutorService executor, long waitTime) {
    executor.shutdown();
    try {
      if (!executor.awaitTermination(waitTime, TimeUnit.SECONDS)) {
        System.out.printf("Задачи выполнялись слишком долго (более %d сек.).\n", waitTime);
      }
    } catch (InterruptedException e) {
      System.out.println("Поток был прерван:" + e.getMessage());
    } finally {
      executor.shutdownNow();
    }
  }
}
