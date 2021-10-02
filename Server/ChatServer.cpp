syntax = "proto3";

   message ServerLogInNotification
   {
     uint32 typeNotification=1;
     string userLogin=2;
     string userPass=3;
     uint32 sesionId=4;
     uint32 userId=5;

     enum Response
       {
         AUTHORIZATION_IS_SUCCESFUL=0;
         AUTHORIZATION_FAILD=1;
         USER_NOT_FOUND=2;
       }
     optional Response respose =6;
     repeated  User user=7;
   }

   message ServerRegistrationNotification
   {
       uint32 typeNotification=1;
       uint32 userId=2;
       uint64 sesionId=3;

        enum Response
          {
            REGISTRATION_IS_SUCCESFUL=0;
            USER_EXISTS=1;
          }
        optional Response response =4;
   }

   message ServerMessageNotification
   {
      uint32 typeNotification=1;
      string userName=2;
      string recipientLogin=3;
      string recipientName=4;
      string text=5;
   }
   message User 
   {
     string name=1;
   }
   

   message NewUserConnectNotification
   {
       uint32 typeNotification=1;
       repeated User user=2;
   }







