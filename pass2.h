int prog_size;

void pass_2()
{
    int start_add, i,locctr,address,flag,length,val,optab_val,symtab_val;
    char opcode[20],label[20],check[20],count[20];

    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("intermediate.txt","r");
    fp4=fopen("output.txt","w");

    fscanf(fp1,"%s %s %X",&label,&opcode,&start_add);
    fprintf(fp4,"%s\t%s\t%X\n",label,opcode,start_add);




    while(!feof(fp1))
    {
        fscanf(fp1,"%X %s %s %s",&locctr,&label,&opcode,&count);


        if(strcmp(label,"-")==0)
        {
            flag=0;
            fp2=fopen("optab.txt","r");
            while(!feof(fp2))
            {
                fscanf(fp2,"%s %d %d",&check,&length,&val);
                if(strcmp(opcode,check)==0)
                {
                    optab_val=val;
                    flag++;
                    break;

                }
            }
            fclose(fp2);

            fp3=fopen("symtab.txt","r");
            while(!feof(fp3))
            {
                fscanf(fp3,"%s %x",&check,&val);
                if(strcmp(count,check)==0)
                {
                    symtab_val=val;
                    flag++;
                    break;
                }
            }
            fclose(fp3);

            if(flag==2)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t%02d%X\n",locctr,label,opcode,count,optab_val,symtab_val);
            }


        /*  else if(strcmp(opcode,"END")==0)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);  //For END
            }
        */


        }


         else
        {

            if(strcmp(opcode,"WORD")==0)
            {
                fprintf(fp4,"%x\t%s\t%s\t%s\t%06s\n",locctr,label,opcode,count,count);
            }


            else if(strcmp(opcode,"BYTE")==0)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t",locctr,label,opcode,count);
                for(i=2;i<strlen(count)-1;i++)
                {
                    fprintf(fp4,"%c",count[i]);
                }
                fprintf(fp4,"\n");
            }

            else if((strcmp(opcode,"RESW")==0) || (strcmp(opcode,"RESB")==0))
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);
            }


            else
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);
            }

        }



    }

    prog_size=locctr-start_add;

    fprintf(fp4,"%X\t%s\t%s\t%s\t-\n",locctr,label,opcode,count);
    fclose(fp4);

    printf("Output.txt file generated\n");
}
