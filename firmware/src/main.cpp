#include <Arduino.h>
#include "main.hpp"


void setup()
{

  Init();

  oled_setup();

  SetupEndstops();

  // pwm.begin();
  // pwm.setOscillatorFrequency(27000000);
  // pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  SetupSteppers();

  DisplayStrings("Setup", "Complete");
}
char timeString[80];

long positions_seek[8];
long positions_reported[8] = {1,1,1,1, 1,1,1,1};

bool CheckPositionsReportedChanged()
{
  bool ret = false;
  for(int i = 0; i < 8; i++)
  {
    if(positions_reported[i] != positions_seek[i])
    {
      ret = true;
      positions_reported[i] = positions_seek[i];
      
    }
  }

  
  return ret;
}
    char str1[16];
    char str2[16];


    long display_throt = 0;
  
void loop()
{
  MoveUpdate();
  if (millis() -display_throt > 500)
  {
   // if (CheckPositionsReportedChanged())
  //  {

      sprintf(str1, "X:%ld Y:%ld\n", GetXPos(), GetYPos());
      sprintf(str2, "Z:%ld W:%ld\n", GetZPos(), GetWPos());
      DisplayStrings(str1, str2);
   // }
   display_throt = millis();
  }
  //LEDToggleX( 5, 100);

  // if(LOW == digitalRead(ENDSTOP_1))
  //   digitalWrite(FAN0, HIGH);
  // else if(HIGH == digitalRead(ENDSTOP_1))
  //   digitalWrite(FAN0, LOW);

  // XMove(100);
  // YMove(-100);
  

  if (Serial.available())
  {
    String line = Serial.readString();

    switch (line[0])
    {
    case 'm':
      switch (line[1])
      {
        case 'o':
        {
          MotorsOff();
        }
        break;
      case 0:
      {
        positions_seek[0] += long((unsigned char)(line[2]) << 24 |
                             (unsigned char)(line[3]) << 16 |
                             (unsigned char)(line[4]) << 8 |
                             (unsigned char)(line[5]));
        XMoveTo(positions_seek[0]);
      }
      break;
      case 1:
      {
        positions_seek[1] += long((unsigned char)(line[2]) << 24 |
                             (unsigned char)(line[3]) << 16 |
                             (unsigned char)(line[4]) << 8 |
                             (unsigned char)(line[5]));
        YMoveTo(positions_seek[1]);
      }
      break;
      case 2:
      {
        positions_seek[2] += long((unsigned char)(line[2]) << 24 |
                             (unsigned char)(line[3]) << 16 |
                             (unsigned char)(line[4]) << 8 |
                             (unsigned char)(line[5]));
        ZMoveTo(positions_seek[2]);
      }
      break;
      case 3:
      {
        positions_seek[3] += long((unsigned char)(line[2]) << 24 |
                             (unsigned char)(line[3]) << 16 |
                             (unsigned char)(line[4]) << 8 |
                             (unsigned char)(line[5]));
        WMoveTo(positions_seek[3]);
      }
      break;
      }
      break;
    case 'f':
      switch (line[1])
      {
      case 0:
        if (line[2] > 0)
          digitalWrite(FAN0, HIGH);
        else
          digitalWrite(FAN0, LOW);
        break;
      case 1:
        if (line[2] > 0)
          digitalWrite(FAN1, HIGH);
        else
          digitalWrite(FAN1, LOW);
        break;
      case 2:
        if (line[2] > 0)
          digitalWrite(FAN2, HIGH);
        else
          digitalWrite(FAN2, LOW);
        break;
      case 3:
        if (line[2] > 0)
          digitalWrite(FAN3, HIGH);
        else
          digitalWrite(FAN3, LOW);
        break;
      case 4:
        if (line[2] > 0)
          digitalWrite(FAN4, HIGH);
        else
          digitalWrite(FAN4, LOW);
        break;
      case 5:
        if (line[2] > 0)
          digitalWrite(FAN5, HIGH);
        else
          digitalWrite(FAN5, LOW);
        break;
      }
      break;
    case 't': // time
      switch (line[1])
      {
      case 's':
        SetTime(
            line[2],
            line[3],
            line[4],
            line[5],
            line[6],
            line[7],
            line[9]);
        DisplayStrings("ts");
        break;
      case 'g':
        DisplayStrings("tg");
        GetTime();
        TimeToString(timeString);
        Serial.write(timeString);
        break;
      default:
        break;
      }

      break;

    default:
      break;
    }
  }
}

/* supply explicit clock init function. To 168MHz from 8MHz HSE Bypass (for nucleo) or 12MHz HSE (Octopus) */
extern "C" void SystemClock_Config(void)
{
#ifdef OCTOPUS_BOARD
#ifdef OCTOPUS_BOARD_FROM_HSI
  /* boot from HSI, internal 16MHz RC, to 168MHz. **NO USB POSSIBLE**, needs HSE! */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
#else
  /* boot from HSE, crystal oscillator (12MHz) */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
#endif
#else
  /* nucleo board, 8MHz external clock input, HSE in bypass mode */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
#endif
}


void ZeroPosition(int pos)
{
  positions_seek[pos] = 0;
}