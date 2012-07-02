/*=========================================================================
 Program:   OsiriX
 
 Copyright (c) OsiriX Team
 All rights reserved.
 Distributed under GNU - LGPL
 
 See http://www.osirix-viewer.com/copyright.html for details.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2ManagedDatabase : NSObject {
	@protected
    NSString* _sqlFilePath;
	@private
	NSManagedObjectContext* _managedObjectContext;
    id _mainDatabase;
    BOOL _isDeallocating;
}

@property(readonly,retain) NSString* sqlFilePath;
@property(readonly) NSManagedObjectModel* managedObjectModel;
@property(readwrite,retain) NSManagedObjectContext* managedObjectContext; // only change this value if you know what you're doing

@property(readonly,retain) id mainDatabase; // for independentDatabases
-(BOOL)isMainDatabase;

// locking actually locks the context
-(void)lock;
-(BOOL)tryLock;
-(void)unlock;
// write locking uses writeLock member
//-(void)writeLock;
//-(BOOL)tryWriteLock;
//-(void)writeUnlock;

+(NSString*) modelName;
-(BOOL) deleteSQLFileIfOpeningFailed;
-(NSManagedObjectModel*)managedObjectModel;
//-(NSMutableDictionary*)persistentStoreCoordinatorsDictionary;
-(BOOL)migratePersistentStoresAutomatically; // default implementation returns YES

-(id)initWithPath:(NSString*)sqlFilePath;
-(id)initWithPath:(NSString*)sqlFilePath context:(NSManagedObjectContext*)context;
-(id)initWithPath:(NSString*)sqlFilePath context:(NSManagedObjectContext*)context mainDatabase:(N2ManagedDatabase*)mainDbReference;

-(NSManagedObjectContext*)independentContext:(BOOL)independent;
-(NSManagedObjectContext*)independentContext;
-(id)independentDatabase;

-(NSEntityDescription*)entityForName:(NSString*)name;

-(id)objectWithID:(id)oid;
-(NSArray*)objectsWithIDs:(NSArray*)objectIDs;

// in these methods, e can be an NSEntityDescription* or an NSString*
-(NSArray*)objectsForEntity:(id)e;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p;
-(NSArray*)objectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)err;
-(NSUInteger)countObjectsForEntity:(id)e;
-(NSUInteger)countObjectsForEntity:(id)e predicate:(NSPredicate*)p;
-(NSUInteger)countObjectsForEntity:(id)e predicate:(NSPredicate*)p error:(NSError**)err;
-(id)newObjectForEntity:(id)e;

-(BOOL)save;
-(BOOL)save:(NSError**)err;

@end

@interface N2ManagedDatabase (Protected)

-(NSManagedObjectContext*)contextAtPath:(NSString*)sqlFilePath;

@end
