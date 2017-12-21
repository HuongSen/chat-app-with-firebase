// Copyright 2017 Google Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "FirebaseDatabase.h"

#include <stdarg.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

#include "FirebaseCocos.h"
#include "firebase/auth.h"
#include "firebase/database.h"
#include "firebase/future.h"

USING_NS_CC;

FirebaseDatabase* FirebaseDatabase::s_instance = NULL;

FirebaseDatabase* FirebaseDatabase::GetInstance()
{
	if (s_instance == NULL) {
		s_instance = new FirebaseDatabase;
	}
	return s_instance;
}

FirebaseDatabase::FirebaseDatabase()
{
	s_instance = this;
}

FirebaseDatabase::~FirebaseDatabase()
{
	delete s_instance;
}

void FirebaseDatabase::Initialize()
{
	void* initialize_targets[] = { &auth_, &database_ };
	CCLOG("Initializing the Database with Firebase API.");
	const firebase::ModuleInitializer::InitializerFn initializers[] = {
		[](firebase::App* app, void* data) {
		// this->logMessage("Attempt to initialize Firebase Auth.");
		void** targets = reinterpret_cast<void**>(data);
		firebase::InitResult result;
		*reinterpret_cast<firebase::auth::Auth**>(targets[0]) =
			firebase::auth::Auth::GetAuth(app, &result);
		return result;
	},
		[](firebase::App* app, void* data) {
		// this->logMessage("Attempt to initialize Firebase Database.");
		void** targets = reinterpret_cast<void**>(data);
		firebase::InitResult result;
		*reinterpret_cast<firebase::database::Database**>(targets[1]) =
			firebase::database::Database::GetInstance(app, &result);
		return result;
	} };
	initializer_.Initialize(
		firebase::App::GetInstance(), initialize_targets, initializers,
		sizeof(initializers) / sizeof(initializers[0]));
}


FirebaseDatabase::State FirebaseDatabase::updateInitialize()
{
	firebase::Future<void> initialize_future =
		initializer_.InitializeLastResult();
	if (initialize_future.status() != firebase::kFutureStatusComplete) {
		return InitializeState;
	}
	if (initialize_future.error() != 0) {
		//logMessage("Failed to initialize Firebase libraries: %s",
			//initialize_future.error_message());
		return RunState;
	}
	//logMessage("Successfully initialized Firebase Auth and Firebase Database.");
	auth_->SignInAnonymously();
	return LoginState;
}

FirebaseDatabase::State FirebaseDatabase::updateLogin()
{
	firebase::Future<firebase::auth::User*> sign_in_future =
		auth_->SignInAnonymouslyLastResult();
	if (sign_in_future.status() != firebase::kFutureStatusComplete) {
		return LoginState;
	}
	if (sign_in_future.error() != firebase::auth::kAuthErrorNone) {
		/*logMessage("ERROR: Could not sign in anonymously. Error %d: %s",
			sign_in_future.error(), sign_in_future.error_message());
		logMessage(
			"Ensure your application has the Anonymous sign-in provider enabled in "
			"the Firebase Console.");*/
		return RunState;
	}
	/*logMessage("Auth: Signed in anonymously.");
	add_listener_button_->setEnabled(true);
	query_button_->setEnabled(true);
	set_button_->setEnabled(true);*/
	return RunState;
}

FirebaseDatabase::State FirebaseDatabase::updateRun()
{
	return RunState;
}