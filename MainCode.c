#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <sys/stat.h>

void NewWindow();
void ClearBuffer();
void Capital_Alphabet(char Enrollment_Number[]);

int main()
{
    // Asking For Choice

    int choice;
    printf("\nEnter '1' If You want to Create New Result\t OR \nEnter '0' If You want to Edit Existing Result\n");
    printf("\n\nEnter Your Choice (0 / 1) : ");
    scanf("%d", &choice);

    // Enter Valid Choice

    if(choice != 0 && choice != 1)
    {
        for(int i=0; ; i++)
        {
            printf("\nEnter Valid Responce..!\n");
            printf("\nEnter Your Choice (0 / 1) : ");
            scanf("%d", &choice);
            if(choice == 1 || choice == 0)
            {
                break;
            }
        }
    }

    ClearBuffer();          // Clearing Buffer

    NewWindow();        // Clearing Display

    //Declaration Of Variables

    char Student_Name[100];
    char Enrollment_Number[15];

    char read_data;
    int track_data;

    char batch[1];

    const char *Subject[] = 
    {
        "C Programming",
        "Calculus",
        "Physics",
        "Energy & Environment Science",
        "Engineering Graphics",
        "Constitution Of India"
    };
    const char *Grade[] =
    {
        "Excellent",
        "Good",
        "Normal",
        "Below Average",
        "Fail"
    };
    int Grade_Length;
    int num_Subject = sizeof(Subject) / sizeof(Subject[0]);
    int Subject_Marks[num_Subject];
    int Size_Subject_Marks = sizeof(Subject_Marks) / sizeof(Subject_Marks[0]);
    int Marks_Digit[num_Subject+1];
    int Total_Marks = 0;
    int Subject_Number;

    int n;

    FILE *Result, *Result_DATA;
    char file_path[150];

    char Enrollment_Number_RESULT[strlen(Enrollment_Number)+6];
    char Enrollment_Number_DATA[strlen(Enrollment_Number)+4];
    char Enrollment_Number_MARK[strlen(Enrollment_Number)+4];
    char Enrollment_Number_NAME[strlen(Enrollment_Number)+4];
    char Enrollment_Number_BATCH[strlen(Enrollment_Number)+5];

    int w = 70; // Width Of Result
    int l = 34; // Length Of Result

    int New_Subject_Marks[Size_Subject_Marks];

    // Creating New Result

    if(choice == 1)
    {
        // Enter Student's Name

        printf("\nEnter Student's Full Name : ");
        for(track_data=0; read_data != '\n'; track_data++)
        {
            scanf("%c", &read_data);
            Student_Name[track_data] = read_data;
        }
        Student_Name[track_data-1] = '\0';
        read_data = 0;

        // Enter Enrollment Number

        printf("\n\nEnter Student's Enrollment Number : ");
        for(track_data=0; read_data != '\n'; track_data++)
        {
            scanf("%c", &read_data);
            Enrollment_Number[track_data] = read_data;
        }
        Enrollment_Number[track_data-1] = '\0';
        read_data = 0;

        Capital_Alphabet(Enrollment_Number);        // Capitalise Small Alphabets

        // Enter Batch

        printf("\n\nEnter Student's Batch (A-D): ");
        scanf("%c", &batch[0]);

        Capital_Alphabet(batch);        // Capitalise Small Alphabets

        ClearBuffer();      // Clearing Buffer

        NewWindow();        // Clearing Display

        // Enter Student's Marks

        printf("\n\nEnter Marks Of Student (Marks Out Of 100): \n");

        for(int input_track=0; input_track<num_Subject; input_track++)
        {
            printf("\n%s : ", Subject[input_track]);
            scanf("%d", &Subject_Marks[input_track]);

            if(Subject_Marks[input_track]<0 || Subject_Marks[input_track]>100)
            {
                // Enter Valid Marks
                while(Subject_Marks[input_track]<0 || Subject_Marks[input_track]>100)
                {
                    printf("\nPlease Enter Valid Marks..!\n\n");
                    printf("%s : ", Subject[input_track]);
                    scanf("%d", &Subject_Marks[input_track]);
                }
            }
        }

        result:         // Returning From Existing Result To Make Change In Result 

        // Creating String Of Result's Data's File Name

        sprintf(Enrollment_Number_RESULT, "%s_RESULT", Enrollment_Number);
        sprintf(Enrollment_Number_DATA, "%s_DATA", Enrollment_Number);
        sprintf(Enrollment_Number_MARK, "%s_MARK", Enrollment_Number);
        sprintf(Enrollment_Number_NAME, "%s_NAME", Enrollment_Number);
        sprintf(Enrollment_Number_BATCH, "%s_BATCH", Enrollment_Number);

        // Total Marks

        for(int i=0; i<num_Subject; i++)
        {
            Total_Marks += Subject_Marks[i];
        }

        // Percentage

        float Percentage = (float)Total_Marks/(float)num_Subject;

        // Number Of Digits Of Marks

        for(int i=0; i<num_Subject+1; i++)
        {
            if(i==num_Subject)
            {
                n=Total_Marks;
                Marks_Digit[i]=0;
                for(int j=0; n!=0; j++)
                {
                    Marks_Digit[i]++;
                    n /= 10;
                }
                break;
            }
            n = Subject_Marks[i];
            Marks_Digit[i]=0;
            for(int j=0; n!=0; j++)
            {
                Marks_Digit[i]++;
                n /= 10;
            }
        }

        NewWindow();        // Clearing Display
    
        // Creating Result Folder

        if(choice == 1)
        {
            if(mkdir(Enrollment_Number) != NULL)
            {
                perror("Error creating the Folder!\n");
            }
        }

        chdir(Enrollment_Number);

        if(choice == 1)
        {
            if(mkdir(Enrollment_Number_DATA) != NULL)
            {
                perror("Error creating the Folder!\n");
            }
        }

        chdir("..");

        // Creating Result Files & Result's Data Files

        sprintf(file_path, "%s\\%s.txt", Enrollment_Number, Enrollment_Number_RESULT);
        Result = fopen(file_path, "w");
        if (Result == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }

        sprintf(file_path, "%s\\%s\\%s", Enrollment_Number, Enrollment_Number_DATA, Enrollment_Number_MARK);
        Result_DATA = fopen(file_path, "wb");
        if (Result_DATA == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }
        fwrite(Subject_Marks, sizeof(int), Size_Subject_Marks, Result_DATA);
        fclose(Result_DATA);

        sprintf(file_path, "%s\\%s\\%s", Enrollment_Number, Enrollment_Number_DATA, Enrollment_Number_NAME);
        Result_DATA = fopen(file_path, "wb");
        if (Result_DATA == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }
        fwrite(Student_Name, sizeof(char), sizeof(Student_Name), Result_DATA);
        fclose(Result_DATA);

        sprintf(file_path, "%s\\%s\\%s", Enrollment_Number, Enrollment_Number_DATA, Enrollment_Number_BATCH);
        Result_DATA = fopen(file_path, "wb");
        if (Result_DATA == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }
        fwrite(batch, sizeof(char), sizeof(batch), Result_DATA);
        fclose(Result_DATA);

        printf("\n");

        // Creating Result's Design

        for(int row=l; row>=1; row--)
        {
            for(int column=w; column>=1; column--)
            {
                // Top & Bottom Line

                if(row==1 || row==l)
                {
                    fprintf(Result, "=");
                }

                // Left & Right Line

                else if(column==1 || column==w)
                {
                    fprintf(Result, "|");
                }

                // College Name

                else if(row==(l-2) && column==(w+46)/2)
                {
                    fprintf(Result, "G H Patel College Of Engineering & Technology ");
                }
                else if((row==(l-2)) && ((column>(w-46)/2) && (column<(w+46)/2)))
                {}
                else if(row==(l-4))
                {
                    fprintf(Result, "-");
                }

                // Student's Information

                else if(row==(l-6) && column==(w-2))
                {
                    fprintf(Result, "Name : ");
                }
                else if(row==(l-6) && column==(w-9))
                {
                    fputs(Student_Name, Result);
                }
                else if((row==(l-6)) && (column<(w-2) && column>(w-9)-strlen(Student_Name)))
                {}
                else if(row==(l-8) && column==(w-2))
                {
                    fprintf(Result, "Enrollment Number : ");
                }
                else if(row==(l-8) && column==(w-21))
                {
                    fputs(Enrollment_Number, Result);
                }
                else if((row==(l-8)) && (column<(w-2) && column>(w-22)-strlen(Enrollment_Number)))
                {}
                else if(row==(l-10) && column==(w-2))
                {
                    fprintf(Result, "Batch : %c", batch[0]);
                }
                else if((row==(l-10)) && (column<(w-2) && column>(w-11)))
                {}
                else if(row==(l-12))
                {
                    fprintf(Result, "-");
                }

                // Subject Marks

                else if(row==(l-14) && column==(w-2))
                {
                    fprintf(Result, "Subject Code");
                }
                else if((row==(l-14)) && (column<(w-2) && column>(w-14)))
                {}
                else if((row<=(l-13) && row>(l-25)) && column==(w-15))
                {
                    fprintf(Result, "|");
                }
                else if(row==(l-14) && column==(w-17))
                {
                    fprintf(Result, "Subject");
                }
                else if((row==(l-14)) && (column<(w-17) && column>(w-24)))
                {}
                else if((row<=(l-13) && row>0) && column==(w-46))
                {
                    fprintf(Result, "|");
                }
                else if(row==(l-14) && column==(w-48))
                {
                    fprintf(Result, "Marks");
                }
                else if((row==(l-14)) && (column<(w-48) && column>(w-53)))
                {}
                else if(row==(l-16) && ((column!=(w-15)) || (column!=(w-46))))
                {
                    fprintf(Result, "-");
                }
                else if(row==(l-18) && column==(w-3))
                {
                    fprintf(Result, "202000110");
                }
                else if(row==(l-19) && column==(w-3))
                {
                    fprintf(Result, "202000104");
                }
                else if(row==(l-20) && column==(w-3))
                {
                    fprintf(Result, "202001213");
                }
                else if(row==(l-21) && column==(w-3))
                {
                    fprintf(Result, "202001207");
                }
                else if(row==(l-22) && column==(w-3))
                {
                    fprintf(Result, "202001208");
                }
                else if(row==(l-23) && column==(w-3))
                {
                    fprintf(Result, "202001206");
                }
                else if((row<=(l-18) && row>=(l-23)) && (column<(w-3) && column>(w-12)))
                {}
                else if(row==(l-18) && column==(w-17))
                {
                    fprintf(Result, "%s", Subject[0]);
                }
                else if(row==(l-18) && (column<(w-17) && column>(w-30)))
                {}
                else if(row==(l-19) && column==(w-17))
                {
                    fprintf(Result, "%s", Subject[1]);
                }
                else if(row==(l-19) && (column<(w-17) && column>(w-25)))
                {}
                else if(row==(l-20) && column==(w-17))
                {
                    fprintf(Result, "%s", Subject[2]);
                }
                else if(row==(l-20) && (column<(w-17) && column>(w-24)))
                {}
                else if(row==(l-21) && column==(w-17))
                {
                    fprintf(Result, "%s", Subject[3]);
                }
                else if(row==(l-21) && (column<(w-17) && column>(w-45)))
                {}
                else if(row==(l-22) && column==(w-17))
                {
                    fprintf(Result, "%s", Subject[4]);
                }
                else if(row==(l-22) && (column<(w-17) && column>(w-37)))
                {}
                else if(row==(l-23) && column==(w-17))
                {
                    fprintf(Result, "%s", Subject[5]);
                }
                else if(row==(l-23) && (column<(w-17) && column>(w-38)))
                {}
                else if(row==(l-18) && column==(w-48))
                {
                    fprintf(Result, "%d", Subject_Marks[0]);
                }
                else if(row==(l-18) && (column<=(w-48) && column>=(w-48-Marks_Digit[0]+1)))
                {}
                else if(row==(l-19) && column==(w-48))
                {
                    fprintf(Result, "%d", Subject_Marks[1]);
                }
                else if(row==(l-19) && (column<=(w-48) && column>=(w-48-Marks_Digit[1]+1)))
                {}
                else if(row==(l-20) && column==(w-48))
                {
                    fprintf(Result, "%d", Subject_Marks[2]);
                }
                else if(row==(l-20) && (column<=(w-48) && column>=(w-48-Marks_Digit[2]+1)))
                {}
                else if(row==(l-21) && column==(w-48))
                {
                    fprintf(Result, "%d", Subject_Marks[3]);
                }
                else if(row==(l-21) && (column<=(w-48) && column>=(w-48-Marks_Digit[3]+1)))
                {}
                else if(row==(l-22) && column==(w-48))
                {
                    fprintf(Result, "%d", Subject_Marks[4]);
                }
                else if(row==(l-22) && (column<=(w-48) && column>=(w-48-Marks_Digit[4]+1)))
                {}
                else if(row==(l-23) && column==(w-48))
                {
                    fprintf(Result, "%d", Subject_Marks[5]);
                }
                else if(row==(l-23) && (column<=(w-48) && column>=(w-48-Marks_Digit[5]+1)))
                {}
                else if(row==(l-25) && ((column!=(w-15)) || (column!=(w-46))))
                {
                    fprintf(Result, "-");
                }
                else if(row==(l-27) && column==(w-40))
                {
                    fprintf(Result, "TOTAL");
                }
                else if(row==(l-27) && (column<(w-40) && column>(w-45)))
                {}
                else if(row==(l-27) && column==(w-48))
                {
                    fprintf(Result, "%d", Total_Marks);
                }
                else if(row==(l-27) && (column<(w-48) && column>(w-48-Marks_Digit[6])))
                {}
                
                // Percentage

                else if(row==(l-28) && column==(w-35))
                {
                    fprintf(Result, "Percentage");
                }
                else if(row==(l-28) && (column<(w-35) && column>(w-45)))
                {}
                else if(row==(l-28) && column==(w-48))
                {
                    fprintf(Result, "%.2f %%", Percentage);
                }
                else if(row==(l-28) && (column<(w-48) && column>(w-48-7)))
                {}

                // Grade

                else if(row==(l-30) && column==(w-40))
                {
                    fprintf(Result, "Grade");
                }
                else if(row==(l-30) && (column<(w-40) && column>(w-40-5)))
                {}
                else if(row==(l-30) && column==(w-48))
                {
                    if(Percentage<=100 && Percentage>=90)
                    {
                        Grade_Length = 9;
                        fprintf(Result, "%s", Grade[0]);
                    }
                    else if(Percentage<90 && Percentage>=80)
                    {
                        Grade_Length = 4;
                        fprintf(Result, "%s", Grade[1]);
                    }
                    else if(Percentage<80 && Percentage>=60)
                    {
                        Grade_Length = 6;
                        fprintf(Result, "%s", Grade[2]);
                    }
                    else if(Percentage<60 && Percentage>=35)
                    {
                        Grade_Length = 13;
                        fprintf(Result, "%s", Grade[3]);
                    }
                    else if(Percentage<35 && Percentage>=0)
                    {
                        Grade_Length = 4;
                        fprintf(Result, "%s", Grade[4]);
                    }
                }
                else if(row==(l-30) && (column<(w-48) && column>(w-48-Grade_Length)))
                {}

                else
                {
                    fprintf(Result, " ");
                }
            }
            fprintf(Result, "\n");
        }
        fclose(Result);

        // End Greeting

        if(choice == 1)
        {
            printf("\nResult for %s has been created Successfully..!!", Enrollment_Number);
        }
        else if(choice == 0)
        {
            printf("\nMarks for %s has been changed Successfully..!!", Enrollment_Number);
        }
    }

    // Changing Existing Result

    else if(choice == 0)
    {
        // Enter Enrollment Number

        printf("\n\nEnter Student's Enrollment Number : ");
        for(track_data=0; read_data != '\n'; track_data++)
        {
            scanf("%c", &read_data);
            Enrollment_Number[track_data] = read_data;
        }
        Enrollment_Number[track_data-1] = '\0';
        read_data = 0;

        Capital_Alphabet(Enrollment_Number);        // Capitalise Small Alphabets

        // Creating String Of Result's Data's File Name

        sprintf(Enrollment_Number_DATA, "%s_DATA", Enrollment_Number);
        sprintf(Enrollment_Number_MARK, "%s_MARK", Enrollment_Number);
        sprintf(Enrollment_Number_NAME, "%s_NAME", Enrollment_Number);
        sprintf(Enrollment_Number_BATCH, "%s_BATCH", Enrollment_Number);

        // Read Data For That Enrollment Number

        sprintf(file_path, "%s\\%s\\%s", Enrollment_Number, Enrollment_Number_DATA, Enrollment_Number_MARK);
        Result_DATA = fopen(file_path, "rb");
        if(Result_DATA == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }
        fread(New_Subject_Marks, sizeof(int), Size_Subject_Marks, Result_DATA);
        fclose(Result_DATA);

        sprintf(file_path, "%s\\%s\\%s", Enrollment_Number, Enrollment_Number_DATA, Enrollment_Number_NAME);
        Result_DATA = fopen(file_path, "rb");
        if(Result_DATA == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }
        fread(Student_Name, sizeof(char), sizeof(Student_Name), Result_DATA);
        fclose(Result_DATA);

        sprintf(file_path, "%s\\%s\\%s", Enrollment_Number, Enrollment_Number_DATA, Enrollment_Number_BATCH);
        Result_DATA = fopen(file_path, "rb");
        if (Result_DATA == NULL) 
        {
            perror("Error creating the file!\n");
            return 1;
        }
        fread(batch, sizeof(char), sizeof(batch), Result_DATA);
        fclose(Result_DATA);

        // Select Subject For Changing Mark

        printf("\n\nEnter Which Subject's Mark You Want to Edit (Please Enter Number 1-6): \n");
        for(int input_track=0; input_track<num_Subject; input_track++)
        {
            printf("\n%d. %s\n",input_track+1, Subject[input_track]);
        }
        printf("\nEnter Number : ");
        scanf("%d", &Subject_Number);
    
        printf("\nEnter Correct (New) Marks Of '%s' : ", Subject[Subject_Number-1]);
        scanf("%d", &New_Subject_Marks[Subject_Number-1]);


        // Enter Valid Marks

        while(New_Subject_Marks[Subject_Number-1]<0 || New_Subject_Marks[Subject_Number-1]>100)
        {
            printf("\nPlease Enter Valid Marks..!\n\n");
            printf("\nEnter Correct (New) Marks Of '%s' : ", Subject[Subject_Number-1]);
            scanf("%d", &New_Subject_Marks[Subject_Number-1]);
        }
    
        for(int i=0; i<num_Subject; i++)
        {
            Subject_Marks[i] = New_Subject_Marks[i];
        }

        goto result;        // Go For Creating Result
    }

    getch();
    return 0;
}

void NewWindow()
{
    printf("\n\nPress Any Key To Continue...\n");
    getch();
    system("cls");
}

void ClearBuffer()
{
    int clearBuffer;
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
}

void Capital_Alphabet(char Enrollment_Number[])
{
    for(int i=0; i<strlen(Enrollment_Number); i++)
    {
        if(Enrollment_Number[i]>=97 && Enrollment_Number[i]<=122)
        {
            Enrollment_Number[i] -= 32;
        }
    }
}