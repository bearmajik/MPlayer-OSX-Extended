/*  
 *  MovieInfo.h
 *  MPlayerOSX Extended
 *  
 *  Created on 02.08.2008
 *  
 *  Description:
 *	Class used to store attributes of a video file.
 *  
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#import <Cocoa/Cocoa.h>
#import "LanguageCodes.h"

static NSString* const MPEMovieInfoAddedExternalSubtitleNotification = @"MPEMovieInfoAddedExternalSubtitleNotification";
static NSString* const MPEMovieInfoAddedExternalSubtitlePathKey = @"MPEMovieInfoAddedExternalSubtitlePathKey";

enum {
	SubtitleTypeAll   = -1,
	SubtitleTypeDemux = 0,
	SubtitleTypeFile  = 1,
	SubtitleTypeVob   = 2,
};
typedef NSInteger SubtitleType;

enum {
	MPEStreamTypeVideo,
	MPEStreamTypeAudio,
	MPEStreamTypeSubtitleDemux,
	MPEStreamTypeSubtitleFile,
	MPEStreamTypeSubtitleVob,
};
typedef NSUInteger MPEStreamType;

@class PlayerController, LocalUserDefaults;

@interface MovieInfo : NSObject {
	
@protected
	
	// General Information
	NSMutableDictionary *info;
	
	// Video streams
	NSMutableDictionary *video;
	// Audio Streams
	NSMutableDictionary *audio;
	// Subtitle Streams
	NSMutableDictionary *subtitle;
	// Subtitle file streams
	NSMutableDictionary *subfile;
	// Subtitle vob streams
	NSMutableDictionary *subvob;
	// Chapter Streams
	NSMutableDictionary *chapter;
	
	// External subtitle files
	NSMutableArray *externalSubtitles;
	
	// Local settings
	LocalUserDefaults *prefs;
	
	// name
	NSString *title;
	NSString *filename;
	unsigned long long filesize;
	NSDate *fileModificationDate;
	NSDate *fileCreationDate;
	
	// formats
	NSString *fileFormat;
	BOOL seekable;
	
	// video
	NSString *videoFormat;
	NSString *videoCodec;
	NSInteger videoBitrate;
	NSInteger videoWidth;
	NSInteger videoHeight;
	float videoFPS;
	float videoAspect;
	
	// audio
	NSString *audioFormat;
	NSString *audioCodec;
	NSInteger audioBitrate;
	float audioSampleRate;
	NSInteger audioChannels;
	
	// length
	NSInteger length;
	
	// statistics
	BOOL captureStats;
	NSMutableDictionary *playbackStats;
	// player playing this item
	PlayerController *player;
}

+ (MovieInfo *)movieInfoWithPathToFile:(NSString*)path;
+ (MovieInfo *)movieInfoFromDictionaryRepresentation:(NSDictionary *)dict;

// serialization
- (NSDictionary *)dictionaryRepresentation;
- (id)initWithDictionaryRepresentation:(NSDictionary *)dict;

// General methods
-(id)init;
-(id)initWithPathToFile:(NSString *)path;
-(void)initializeInstance;
-(BOOL)containsInfo;
-(BOOL)fileIsValid;
-(void)preflight;

// format methods
-(BOOL)isVideo;

// basic info
@property (nonatomic,retain) NSString *title;
@property (nonatomic,readonly) NSString* displayName;
@property (nonatomic,retain) NSString* filename;
@property (nonatomic,retain) NSString* fileFormat;
@property (nonatomic,getter=isSeekable) BOOL seekable;
@property (nonatomic,readonly) NSString* displayLength;
@property (nonatomic) NSInteger length;

// file attributes (set automatically with setFilename:)
@property (nonatomic) unsigned long long filesize;
@property (nonatomic,readonly) NSString* displayFilesize; 
@property (nonatomic,retain) NSDate *fileModificationDate;
@property (nonatomic,retain) NSDate *fileCreationDate;

// video properties
@property (nonatomic,retain) NSString* videoFormat;
@property (nonatomic,retain) NSString* videoCodec;
@property (nonatomic) NSInteger videoBitrate;
@property (nonatomic) NSInteger videoWidth;
@property (nonatomic) NSInteger videoHeight;
@property (nonatomic) float videoFPS;
@property (nonatomic) float videoAspect;

// audio properties
@property (nonatomic,retain) NSString* audioFormat;
@property (nonatomic,retain) NSString* audioCodec;
@property (nonatomic) NSInteger audioBitrate;
@property (nonatomic) float audioSampleRate;
@property (nonatomic) NSInteger audioChannels; 

// local preferences
@property (nonatomic, readonly) LocalUserDefaults *prefs;

// playback statistics
@property (nonatomic) BOOL captureStats;
@property (retain) NSMutableDictionary *playbackStats;
@property (nonatomic,retain) PlayerController *player;

// external subtitles
- (void)addExternalSubtitle:(NSString *)path;
- (NSUInteger)externalSubtitleCount;
@property (nonatomic,readonly) NSArray* externalSubtitles;

// Set and get info
-(void)setInfo:(NSString *)value forKey:(NSString *)key;
-(NSString *)getInfoForKey:(NSString *)key;

// Set and get video streams
-(void)newVideoStream:(unsigned int)streamId;
-(void)setVideoStreamName:(NSString *)streamName forId:(unsigned int)streamId;
-(NSString *)videoNameForStream:(unsigned int)streamId;
-(NSUInteger)videoStreamCount;
-(NSEnumerator *)getVideoStreamsEnumerator;
-(NSString *)descriptionForVideoStream:(unsigned int)streamId;

// Set and get audio streams
-(void)newAudioStream:(unsigned int)streamId;
-(void)setAudioStreamName:(NSString *)streamName forId:(unsigned int)streamId;
-(void)setAudioStreamLanguage:(NSString *)streamLanguage forId:(unsigned int)streamId;
-(NSString *)audioNameForStream:(unsigned int)streamId;
-(NSString *)audioLanguageForStream:(unsigned int)streamId;
-(NSUInteger)audioStreamCount;
-(NSEnumerator *)getAudioStreamsEnumerator;
-(NSString *)descriptionForAudioStream:(unsigned int)streamId;

// Set and get subtitle streams
-(void)newSubtitleStream:(unsigned int)streamId forType:(SubtitleType)type;
-(void)setSubtitleStreamName:(NSString *)streamName forId:(unsigned int)streamId andType:(SubtitleType)type;
-(void)setSubtitleStreamLanguage:(NSString *)streamLanguage forId:(unsigned int)streamId andType:(SubtitleType)type;
-(NSString *)subtitleNameForStream:(unsigned int)streamId andType:(SubtitleType)type;
-(NSString *)subtitleLanguageForStream:(unsigned int)streamId andType:(SubtitleType)type;
-(NSUInteger)subtitleCountForType:(SubtitleType)type;
-(NSEnumerator *)getSubtitleStreamsEnumeratorForType:(SubtitleType)type;
-(NSString *)descriptionForSubtitleStream:(unsigned int)streamId andType:(SubtitleType)type;

// Set and get chapters
-(void)newChapter:(unsigned int)chapterId;
-(void)setChapterStartTime:(NSNumber *)startTime forId:(unsigned int)chapterId;
-(void)setChapterName:(NSString *)chapterName forId:(unsigned int)chapterId;
-(NSString *)nameForChapter:(unsigned int)chapterId;
-(float)startOfChapter:(unsigned int)chapterId;
-(NSUInteger)chapterCount;
-(NSEnumerator *)getChaptersEnumerator;

-(NSMutableDictionary *)subDictForType:(SubtitleType)type;

@end


@protocol MovieInfoProvider <NSObject>
- (MovieInfo *)currentMovieInfo;
@end

